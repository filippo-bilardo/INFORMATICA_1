#!/bin/bash

# Git Rebase & Cherry-Pick Automation Script
# Automazione per operazioni Git avanzate con sicurezza integrata

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
BACKUP_PREFIX="backup"
MAX_BACKUP_AGE_DAYS=30
SCRIPT_VERSION="1.0.0"

# Logging
log() {
    echo -e "${GREEN}[$(date +'%Y-%m-%d %H:%M:%S')] $1${NC}"
}

warn() {
    echo -e "${YELLOW}[WARNING] $1${NC}"
}

error() {
    echo -e "${RED}[ERROR] $1${NC}"
    exit 1
}

# Help function
show_help() {
    cat << EOF
🚀 Git Rebase & Cherry-Pick Automation Script v${SCRIPT_VERSION}

USAGE:
    $0 [COMMAND] [OPTIONS]

COMMANDS:
    safe-rebase <target-branch>     - Rebase with automatic backup and safety checks
    interactive-cleanup             - Interactive rebase for commit cleanup
    cherry-pick-range <start> <end> - Cherry-pick commit range safely
    emergency-recovery              - Recover from failed operations
    health-check                    - Check repository health
    cleanup-backups                 - Remove old backup tags
    conflict-analysis <branch>      - Analyze potential conflicts before merge

SAFETY FEATURES:
    ✅ Automatic backups before operations
    ✅ Pre-operation safety checks
    ✅ Conflict prediction
    ✅ Recovery assistance
    ✅ Team notification support

EXAMPLES:
    $0 safe-rebase main
    $0 interactive-cleanup
    $0 cherry-pick-range abc123 def456
    $0 conflict-analysis feature-branch

OPTIONS:
    -h, --help              Show this help message
    -v, --verbose           Enable verbose output
    -f, --force            Skip safety confirmations (dangerous!)
    --dry-run              Show what would be done without executing
    --backup-prefix PREFIX Use custom prefix for backup tags

ENVIRONMENT VARIABLES:
    GIT_AUTOMATION_TEAM_HOOK   - URL for team notifications
    GIT_AUTOMATION_SLACK_HOOK  - Slack webhook for notifications
EOF
}

# Utility functions
check_git_repo() {
    if ! git rev-parse --git-dir > /dev/null 2>&1; then
        error "Not in a Git repository"
    fi
}

check_clean_working_directory() {
    if ! git diff-index --quiet HEAD --; then
        warn "Working directory is not clean"
        if [[ "${FORCE:-false}" != "true" ]]; then
            echo "Uncommitted changes found:"
            git status --porcelain
            echo ""
            read -p "Continue anyway? (y/N): " -n 1 -r
            echo
            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                error "Operation cancelled"
            fi
        fi
        
        log "Stashing uncommitted changes..."
        git stash push -m "Auto-stash before rebase operation $(date)"
        STASH_CREATED="true"
    fi
}

create_backup() {
    local current_branch=$(git branch --show-current)
    local timestamp=$(date +%Y%m%d-%H%M%S)
    local backup_name="${BACKUP_PREFIX}-${current_branch}-${timestamp}"
    
    log "Creating backup tag: ${backup_name}"
    git tag "${backup_name}"
    
    echo "${backup_name}"
}

fetch_updates() {
    log "Fetching latest changes from remote..."
    git fetch --all --prune
}

analyze_conflicts() {
    local target_branch="$1"
    local current_branch=$(git branch --show-current)
    
    log "Analyzing potential conflicts between ${current_branch} and ${target_branch}..."
    
    # Get merge base
    local merge_base=$(git merge-base HEAD "${target_branch}")
    
    # Check for conflicts using merge-tree
    local conflict_output=$(git merge-tree "${merge_base}" HEAD "${target_branch}" 2>/dev/null || true)
    
    if echo "${conflict_output}" | grep -q "<<<<<<< "; then
        local conflict_count=$(echo "${conflict_output}" | grep -c "<<<<<<< " || true)
        warn "Potential conflicts detected: ${conflict_count} files"
        
        # Show conflicting files
        echo "Files with potential conflicts:"
        git diff --name-only "${merge_base}" HEAD
        git diff --name-only "${merge_base}" "${target_branch}"
        
        return 1
    else
        log "No conflicts detected"
        return 0
    fi
}

send_team_notification() {
    local message="$1"
    local webhook_url="${GIT_AUTOMATION_TEAM_HOOK:-}"
    
    if [[ -n "${webhook_url}" ]]; then
        curl -s -X POST "${webhook_url}" \
            -H "Content-Type: application/json" \
            -d "{\"text\": \"🔧 Git Automation: ${message}\"}" > /dev/null || true
    fi
}

# Main commands
safe_rebase() {
    local target_branch="$1"
    
    if [[ -z "${target_branch}" ]]; then
        error "Target branch not specified"
    fi
    
    check_git_repo
    check_clean_working_directory
    fetch_updates
    
    local current_branch=$(git branch --show-current)
    log "Starting safe rebase of ${current_branch} onto ${target_branch}"
    
    # Create backup
    local backup_tag=$(create_backup)
    
    # Analyze potential conflicts
    if ! analyze_conflicts "${target_branch}"; then
        if [[ "${FORCE:-false}" != "true" ]]; then
            read -p "Conflicts detected. Continue with rebase? (y/N): " -n 1 -r
            echo
            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                error "Rebase cancelled"
            fi
        fi
    fi
    
    # Perform rebase
    log "Executing rebase..."
    if git rebase "${target_branch}"; then
        log "✅ Rebase completed successfully"
        send_team_notification "Rebase of ${current_branch} onto ${target_branch} completed successfully"
    else
        error "❌ Rebase failed. Use 'git rebase --abort' to cancel or resolve conflicts manually."
    fi
    
    # Restore stash if created
    if [[ "${STASH_CREATED:-false}" == "true" ]]; then
        log "Restoring stashed changes..."
        git stash pop
    fi
    
    log "Backup available at tag: ${backup_tag}"
}

interactive_cleanup() {
    check_git_repo
    check_clean_working_directory
    
    local current_branch=$(git branch --show-current)
    log "Starting interactive cleanup for ${current_branch}"
    
    # Create backup
    local backup_tag=$(create_backup)
    
    # Get number of commits to clean up
    echo "Recent commits:"
    git log --oneline -10
    echo ""
    
    read -p "How many commits back do you want to clean up? (default: 5): " commit_count
    commit_count=${commit_count:-5}
    
    log "Starting interactive rebase for last ${commit_count} commits..."
    log "Available commands in editor:"
    log "  pick   = use commit"
    log "  reword = use commit, but edit the commit message"
    log "  edit   = use commit, but stop for amending"
    log "  squash = use commit, but meld into previous commit"
    log "  fixup  = like squash, but discard this commit's log message"
    log "  drop   = remove commit"
    
    if git rebase -i "HEAD~${commit_count}"; then
        log "✅ Interactive rebase completed successfully"
    else
        error "❌ Interactive rebase failed. Resolve conflicts or use 'git rebase --abort'"
    fi
    
    log "Backup available at tag: ${backup_tag}"
}

cherry_pick_range() {
    local start_commit="$1"
    local end_commit="$2"
    
    if [[ -z "${start_commit}" || -z "${end_commit}" ]]; then
        error "Start and end commits must be specified"
    fi
    
    check_git_repo
    check_clean_working_directory
    
    local current_branch=$(git branch --show-current)
    log "Cherry-picking range ${start_commit}..${end_commit} to ${current_branch}"
    
    # Create backup
    local backup_tag=$(create_backup)
    
    # Validate commits exist
    if ! git rev-parse --verify "${start_commit}" > /dev/null 2>&1; then
        error "Start commit ${start_commit} not found"
    fi
    
    if ! git rev-parse --verify "${end_commit}" > /dev/null 2>&1; then
        error "End commit ${end_commit} not found"
    fi
    
    # Show commits to be cherry-picked
    echo "Commits to be cherry-picked:"
    git log --oneline "${start_commit}^..${end_commit}"
    echo ""
    
    if [[ "${FORCE:-false}" != "true" ]]; then
        read -p "Proceed with cherry-pick? (y/N): " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            error "Cherry-pick cancelled"
        fi
    fi
    
    # Perform cherry-pick
    if git cherry-pick "${start_commit}^..${end_commit}"; then
        log "✅ Cherry-pick completed successfully"
    else
        error "❌ Cherry-pick failed. Resolve conflicts and use 'git cherry-pick --continue'"
    fi
    
    log "Backup available at tag: ${backup_tag}"
}

emergency_recovery() {
    check_git_repo
    
    log "🆘 Emergency Recovery Mode"
    echo ""
    echo "Available recovery options:"
    echo "1. Abort current rebase/merge/cherry-pick"
    echo "2. Reset to last backup tag"
    echo "3. Show reflog for manual recovery"
    echo "4. Check for dangling commits"
    echo "5. Cancel"
    echo ""
    
    read -p "Select option (1-5): " -n 1 -r option
    echo ""
    
    case $option in
        1)
            log "Aborting current operations..."
            git rebase --abort 2>/dev/null || true
            git merge --abort 2>/dev/null || true
            git cherry-pick --abort 2>/dev/null || true
            git am --abort 2>/dev/null || true
            log "✅ Operations aborted"
            ;;
        2)
            log "Available backup tags:"
            git tag -l "${BACKUP_PREFIX}-*" | sort -r | head -10
            echo ""
            read -p "Enter backup tag name: " backup_tag
            if [[ -n "${backup_tag}" ]]; then
                log "Resetting to ${backup_tag}..."
                git reset --hard "${backup_tag}"
                log "✅ Reset completed"
            fi
            ;;
        3)
            log "Recent reflog entries:"
            git reflog -20
            echo ""
            log "Use 'git reset --hard HEAD@{N}' to recover"
            ;;
        4)
            log "Checking for dangling commits..."
            git fsck --lost-found
            ;;
        5)
            log "Recovery cancelled"
            ;;
        *)
            error "Invalid option"
            ;;
    esac
}

health_check() {
    check_git_repo
    
    log "🏥 Repository Health Check"
    echo ""
    
    # Basic info
    echo "📊 Repository Information:"
    echo "  Current branch: $(git branch --show-current)"
    echo "  Total commits: $(git rev-list --count HEAD)"
    echo "  Repository size: $(du -sh .git | cut -f1)"
    echo ""
    
    # Check integrity
    echo "🔍 Integrity Check:"
    if git fsck --quiet 2>/dev/null; then
        echo "  ✅ Repository integrity: OK"
    else
        echo "  ❌ Repository integrity: ISSUES FOUND"
        git fsck
    fi
    echo ""
    
    # Dangling objects
    local dangling_count=$(git fsck --lost-found 2>/dev/null | grep "dangling" | wc -l)
    echo "🗑️  Dangling objects: ${dangling_count}"
    echo ""
    
    # Backup tags
    local backup_count=$(git tag -l "${BACKUP_PREFIX}-*" | wc -l)
    echo "💾 Backup tags: ${backup_count}"
    if [[ ${backup_count} -gt 0 ]]; then
        echo "  Latest: $(git tag -l "${BACKUP_PREFIX}-*" | sort -r | head -1)"
    fi
    echo ""
    
    # Remote sync status
    echo "🌐 Remote Sync Status:"
    git fetch --dry-run 2>&1 | head -5 || echo "  Remote fetch failed"
    echo ""
    
    # Recommendations
    echo "💡 Recommendations:"
    if [[ ${dangling_count} -gt 50 ]]; then
        echo "  - Consider running 'git gc' to clean up"
    fi
    if [[ ${backup_count} -gt 20 ]]; then
        echo "  - Consider cleaning old backup tags"
    fi
    echo "  - Regular 'git gc --auto' keeps repository optimized"
}

cleanup_backups() {
    check_git_repo
    
    log "🧹 Cleaning up old backup tags (older than ${MAX_BACKUP_AGE_DAYS} days)"
    
    local current_timestamp=$(date +%s)
    local deleted_count=0
    
    for tag in $(git tag -l "${BACKUP_PREFIX}-*"); do
        # Get tag creation date
        local tag_timestamp=$(git log -1 --format=%ct "$tag" 2>/dev/null || echo "0")
        local age_days=$(( (current_timestamp - tag_timestamp) / 86400 ))
        
        if [[ ${age_days} -gt ${MAX_BACKUP_AGE_DAYS} ]]; then
            log "Deleting old backup: ${tag} (${age_days} days old)"
            git tag -d "${tag}"
            ((deleted_count++))
        fi
    done
    
    log "✅ Cleanup completed. Deleted ${deleted_count} old backup tags"
}

conflict_analysis() {
    local target_branch="$1"
    
    if [[ -z "${target_branch}" ]]; then
        error "Target branch not specified"
    fi
    
    check_git_repo
    
    log "🔍 Detailed Conflict Analysis"
    
    # Basic info
    local current_branch=$(git branch --show-current)
    local merge_base=$(git merge-base HEAD "${target_branch}")
    
    echo "📊 Analysis Details:"
    echo "  Source branch: ${current_branch}"
    echo "  Target branch: ${target_branch}"
    echo "  Merge base: ${merge_base:0:8}"
    echo ""
    
    # File changes
    echo "📁 Modified Files:"
    echo "  In ${current_branch}:"
    git diff --name-only "${merge_base}" HEAD | sed 's/^/    /'
    echo "  In ${target_branch}:"
    git diff --name-only "${merge_base}" "${target_branch}" | sed 's/^/    /'
    echo ""
    
    # Conflict prediction
    if analyze_conflicts "${target_branch}"; then
        echo "✅ No conflicts predicted"
    else
        echo "⚠️  Conflicts likely in shared modified files"
        echo ""
        echo "🛠️  Conflict Resolution Strategy:"
        echo "   1. Use 'git mergetool' for complex conflicts"
        echo "   2. Consider incremental merge for large conflicts"
        echo "   3. Coordinate with team for shared file changes"
    fi
}

# Main script logic
main() {
    case "${1:-}" in
        "safe-rebase")
            safe_rebase "$2"
            ;;
        "interactive-cleanup")
            interactive_cleanup
            ;;
        "cherry-pick-range")
            cherry_pick_range "$2" "$3"
            ;;
        "emergency-recovery")
            emergency_recovery
            ;;
        "health-check")
            health_check
            ;;
        "cleanup-backups")
            cleanup_backups
            ;;
        "conflict-analysis")
            conflict_analysis "$2"
            ;;
        "-h"|"--help"|"help")
            show_help
            ;;
        "")
            error "No command specified. Use --help for usage information."
            ;;
        *)
            error "Unknown command: $1. Use --help for usage information."
            ;;
    esac
}

# Parse global options
while [[ $# -gt 0 ]]; do
    case $1 in
        -v|--verbose)
            set -x
            shift
            ;;
        -f|--force)
            FORCE="true"
            shift
            ;;
        --dry-run)
            DRY_RUN="true"
            shift
            ;;
        --backup-prefix)
            BACKUP_PREFIX="$2"
            shift 2
            ;;
        *)
            break
            ;;
    esac
done

# Execute main function with remaining arguments
main "$@"
