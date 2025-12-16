# VulpOS - Custom Linux Operating System
## Project Plan

---

## Overview
Build a Linux-based operating system from scratch with a GitHub-based package management system. The OS will bootstrap from kernel to a minimal userland, then use GitHub repositories as the source for all system packages.

**GitHub Organization:** https://github.com/orgs/Vulps-OS/repositories

---

## Phase 1: Kernel Boot
**Goal:** Get Linux kernel booting without errors

**Deliverables:**
- Compiled Linux kernel (6.6 LTS)
- Successful boot in QEMU showing boot messages
- Kernel panic expected (no init found) - this is success at this stage

**Success Criteria:**
- Boot messages appear
- No kernel compilation errors
- Kernel doesn't crash before looking for init

---

## Phase 2: Echo Shell
**Goal:** First functional userland - prove we can run code on top of the kernel

**Components to Build:**
1. Init program (PID 1) - launches the shell
2. Echo shell - displays prompt, reads input, echoes it back
3. Initramfs - packages these programs into bootable filesystem

**Deliverables:**
- Working init binary
- Working shell binary that echoes user input
- Initramfs containing both
- Kernel boots to shell prompt

**Success Criteria:**
- System boots without kernel panic
- Prompt appears: `vulpos> `
- Typing text echoes it back
- Ctrl+C doesn't crash the system

---

## Phase 3: GitHub Package Manager
**Goal:** Replace traditional package management with GitHub-based system

### 3.1 Architecture Design

**Package Definition:**
- Each package = one GitHub repository
- Repository must contain:
  - `build.sh` - how to compile/install
  - `manifest.json` - metadata (dependencies, version, description)
  - Source code

**Core Package List (Bootstrap):**
- Maintained in main OS repository
- JSON file listing required repos for minimal system
- Includes: shell utilities, core commands, package manager itself

**Package Manager Features:**
- Clone repos from GitHub
- Parse manifest.json for dependencies
- Execute build scripts
- Track installed packages
- Handle updates (git pull)

### 3.2 Implementation Phases

#### 3.2.1 Package Manager Core
**Components:**
- GitHub API client (fetch repo lists, clone repos)
- Manifest parser
- Dependency resolver
- Build executor
- Installation tracker (database of installed packages)

**Deliverables:**
- `vpm` (Vulp Package Manager) binary
- Can list available packages from org
- Can clone and build a single package
- Tracks what's installed

#### 3.2.2 Bootstrap Repository Structure
**Setup:**
- Create GitHub organization (e.g., `vulpos-packages`)
- Create repositories for core utilities:
  - `vulpos-shell` - actual shell implementation
  - `vulpos-coreutils` - ls, mkdir, cat, etc.
  - `vulpos-vpm` - package manager itself
  - `vulpos-init` - proper init system
  - `vulpos-libc` - C library wrapper (or just use musl)

**Deliverables:**
- Organization created
- Core package repos created with proper structure
- Each repo has build.sh and manifest.json

#### 3.2.3 Integration
**Components:**
- Modify initramfs to include minimal vpm
- Create bootstrap script that runs on first boot
- Script fetches core package list and installs essentials

**Deliverables:**
- System can boot with just kernel + minimal vpm
- First boot automatically installs core packages from GitHub
- Subsequent boots use installed packages

---

## Phase 4: Core Utilities
**Goal:** Implement essential commands to make system usable

**Package Repositories to Create:**
- File operations: ls, cd, mkdir, rm, cp, mv, touch
- Text operations: cat, echo, grep, sed
- System: ps, kill, mount, umount
- Network: wget, curl (for vpm to function)

**Deliverables:**
- Each command in separate repo
- All installable via vpm
- Basic system functionality achieved

---

## Phase 5: Polish & Expansion
**Goal:** Make system practical and extensible

**Features:**
- User management
- Proper filesystem hierarchy (/etc, /home, /var, etc)
- Configuration management
- Package versioning and updates
- Package search/browse functionality
- Multi-user support

---

## Technical Decisions

### Why GitHub as Package Manager?
**Pros:**
- Built-in version control
- Free hosting
- API for automation
- Familiar to developers
- Easy contribution model (PRs)
- Built-in issue tracking per package

**Cons:**
- Requires internet for package installation
- Dependent on GitHub availability
- No binary package caching (everything builds from source)

**Mitigation:**
- Cache compiled packages locally after first build
- Support for mirror organizations
- Offline mode using cached packages

### Build System
- C for core components (init, shell, utilities)
- Bash for build scripts
- JSON for manifests (easy to parse in C)

### Filesystem
- Initramfs for bootstrap (CPIO archive)
- Transition to proper ext4 root filesystem after package manager is running

---

## Success Milestones

1. ✅ Kernel boots in QEMU
2. ✅ Echo shell responds to input
3. ✅ Package manager can list repos from GitHub org
4. ✅ Package manager can install one package
5. ✅ System boots and auto-installs core packages
6. ✅ Basic file operations work (ls, mkdir, etc)
7. ✅ System is self-hosting (can rebuild itself)

---

## Development Environment
- Host: Debian 12 in Hyper-V VM
- Test: QEMU inside Debian
- Source Control: Git/GitHub
- Build Tools: GCC, make, binutils
- Debugging: GDB with QEMU

---

## Notes & Considerations

**Security:**
- Running random build scripts from GitHub is inherently risky
- Consider: GPG signing of repos, checksum verification
- Future: sandboxed builds

**Performance:**
- Building from source is slow
- Future: optional binary cache server
- Use ccache for faster rebuilds during development

**Dependency Hell:**
- Keep dependencies minimal
- Static linking where practical
- Clear dependency tree in manifests

**Naming:**
- VulpOS - the operating system
- vpm - Vulp Package Manager
- vulpos-* - package repository naming convention
