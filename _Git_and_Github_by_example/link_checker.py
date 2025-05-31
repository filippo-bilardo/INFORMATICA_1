#!/usr/bin/env python3
"""
Link Checker for GitGithubByExample Repository
Checks all README.md files for broken internal and external links
"""

import os
import re
import requests
from pathlib import Path
from urllib.parse import urljoin, urlparse
import time

class LinkChecker:
    def __init__(self, root_dir):
        self.root_dir = Path(root_dir)
        self.internal_links = []
        self.external_links = []
        self.broken_internal = []
        self.broken_external = []
        
    def find_readme_files(self):
        """Find all README.md files in the repository"""
        return list(self.root_dir.rglob("README.md"))
    
    def extract_links(self, file_path):
        """Extract all links from a markdown file"""
        try:
            with open(file_path, 'r', encoding='utf-8') as file:
                content = file.read()
        except UnicodeDecodeError:
            with open(file_path, 'r', encoding='latin-1') as file:
                content = file.read()
        
        # Regex patterns for different link types
        patterns = [
            r'\[([^\]]+)\]\(([^)]+)\)',  # [text](url)
            r'!\[([^\]]*)\]\(([^)]+)\)', # ![alt](image)
            r'<a[^>]+href=["\']([^"\']+)["\'][^>]*>',  # <a href="url">
            r'<img[^>]+src=["\']([^"\']+)["\'][^>]*>'   # <img src="url">
        ]
        
        links = []
        for pattern in patterns:
            matches = re.findall(pattern, content)
            for match in matches:
                if isinstance(match, tuple):
                    if len(match) == 2:
                        links.append(match[1])  # URL from [text](url) or ![alt](url)
                    else:
                        links.append(match[0])  # URL from href or src
                else:
                    links.append(match)
        
        return links
    
    def categorize_links(self, links, file_path):
        """Categorize links as internal or external"""
        for link in links:
            # Skip anchors and mailto links
            if link.startswith('#') or link.startswith('mailto:'):
                continue
                
            if link.startswith('http://') or link.startswith('https://'):
                self.external_links.append((str(file_path), link))
            else:
                # Internal link - resolve relative to file location
                if link.startswith('/'):
                    # Absolute path from repository root
                    resolved_path = self.root_dir / link.lstrip('/')
                else:
                    # Relative path from current file
                    resolved_path = file_path.parent / link
                
                self.internal_links.append((str(file_path), link, str(resolved_path)))
    
    def check_internal_links(self):
        """Check if internal links point to existing files"""
        print("🔍 Checking internal links...")
        
        for file_path, original_link, resolved_path in self.internal_links:
            path_obj = Path(resolved_path)
            
            # Remove fragment identifier
            if '#' in str(path_obj):
                path_obj = Path(str(path_obj).split('#')[0])
            
            if not path_obj.exists():
                self.broken_internal.append((file_path, original_link, str(path_obj)))
                print(f"❌ {file_path}: {original_link} -> {path_obj} (NOT FOUND)")
    
    def check_external_links(self, timeout=10):
        """Check if external links are accessible"""
        print("🌐 Checking external links...")
        
        session = requests.Session()
        session.headers.update({
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        })
        
        for file_path, link in self.external_links:
            try:
                response = session.head(link, timeout=timeout, allow_redirects=True)
                if response.status_code >= 400:
                    self.broken_external.append((file_path, link, response.status_code))
                    print(f"❌ {file_path}: {link} (Status: {response.status_code})")
                else:
                    print(f"✅ {link}")
            except requests.exceptions.RequestException as e:
                self.broken_external.append((file_path, link, str(e)))
                print(f"❌ {file_path}: {link} (Error: {str(e)[:100]})")
            
            # Rate limiting
            time.sleep(0.5)
    
    def generate_report(self):
        """Generate a comprehensive report"""
        total_internal = len(self.internal_links)
        total_external = len(self.external_links)
        broken_internal_count = len(self.broken_internal)
        broken_external_count = len(self.broken_external)
        
        print("\n" + "="*80)
        print("📊 LINK CHECKER REPORT")
        print("="*80)
        
        print(f"\n📁 Internal Links:")
        print(f"   Total: {total_internal}")
        print(f"   Working: {total_internal - broken_internal_count}")
        print(f"   Broken: {broken_internal_count}")
        
        print(f"\n🌐 External Links:")
        print(f"   Total: {total_external}")
        print(f"   Working: {total_external - broken_external_count}")
        print(f"   Broken: {broken_external_count}")
        
        if broken_internal_count > 0:
            print(f"\n❌ BROKEN INTERNAL LINKS ({broken_internal_count}):")
            for file_path, link, resolved_path in self.broken_internal:
                print(f"   • {file_path}")
                print(f"     Link: {link}")
                print(f"     Resolved to: {resolved_path}")
                print()
        
        if broken_external_count > 0:
            print(f"\n❌ BROKEN EXTERNAL LINKS ({broken_external_count}):")
            for file_path, link, error in self.broken_external:
                print(f"   • {file_path}")
                print(f"     Link: {link}")
                print(f"     Error: {error}")
                print()
        
        success_rate_internal = ((total_internal - broken_internal_count) / total_internal * 100) if total_internal > 0 else 100
        success_rate_external = ((total_external - broken_external_count) / total_external * 100) if total_external > 0 else 100
        
        print(f"\n📈 Success Rates:")
        print(f"   Internal Links: {success_rate_internal:.1f}%")
        print(f"   External Links: {success_rate_external:.1f}%")
        print(f"   Overall: {((total_internal + total_external - broken_internal_count - broken_external_count) / (total_internal + total_external) * 100):.1f}%")
        
        return {
            'internal_total': total_internal,
            'internal_broken': broken_internal_count,
            'external_total': total_external,
            'external_broken': broken_external_count
        }

def main():
    """Main function to run the link checker"""
    root_dir = Path(__file__).parent
    
    print("🔍 Starting Link Checker for GitGithubByExample")
    print(f"📁 Repository root: {root_dir}")
    
    checker = LinkChecker(root_dir)
    
    # Find all README files
    readme_files = checker.find_readme_files()
    print(f"\n📄 Found {len(readme_files)} README.md files")
    
    # Extract and categorize links
    for readme_file in readme_files:
        print(f"Processing: {readme_file}")
        links = checker.extract_links(readme_file)
        checker.categorize_links(links, readme_file)
    
    print(f"\n📊 Found {len(checker.internal_links)} internal and {len(checker.external_links)} external links")
    
    # Check links
    checker.check_internal_links()
    checker.check_external_links()
    
    # Generate report
    report = checker.generate_report()
    
    # Exit with error code if broken links found
    if report['internal_broken'] > 0 or report['external_broken'] > 0:
        print(f"\n⚠️  Found {report['internal_broken'] + report['external_broken']} broken links")
        return 1
    else:
        print(f"\n✅ All links are working!")
        return 0

if __name__ == "__main__":
    exit(main())
