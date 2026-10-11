# NanoOS

**A custom desktop environment built with C++ and raylib.**

NanoOS is a desktop-environment application designed to run on Windows 11. It aims to recreate the experience of using a lightweight operating system, with its own desktop interface, window manager, terminal, file manager, and applications.

NanoOS is a regular Windows application, not a standalone operating system or Linux distribution.

## Project Goals

* Build a custom desktop interface using C++ and raylib.
* Create an interactive desktop with a taskbar and Start menu.
* Implement an internal window manager.
* Develop a custom terminal and command interpreter.
* Build a file manager and settings application.
* Design modular, maintainable source code.
* Compile and test each module before moving to the next stage.

## Technology Stack

| Component             | Technology         |
| --------------------- | ------------------ |
| Programming language  | C++                |
| Graphics and input    | raylib             |
| Target platform       | Windows 11         |
| Compiler              | GCC (MSYS2 UCRT64) |
| Build system          | GNU Make           |
| Project configuration | Makefile           |

## Planned Features

### Desktop Environment

* Custom wallpaper and desktop background
* Taskbar
* Start menu
* Application launcher
* Desktop icons

### Window Manager

* Multiple internal application windows
* Window dragging
* Minimize, maximize, and close controls
* Window focus and activation
* Basic window arrangement

### Terminal

* Custom command interpreter
* Command history
* Built-in commands such as `help`, `clear`, `pwd`, `ls`, and `cd`
* Command output and error handling

### Applications

* File Manager
* Settings
* Terminal
* Additional built-in applications

### Virtual File System

* A dedicated internal file and directory model
* Navigation and file operations
* Optional access to selected Windows directories

## Project Structure

The source tree will grow as features are implemented and tested.

```text
NanoOS/
├── src/
│   └── main.cpp
├── assets/
│   ├── icons/
│   ├── fonts/
│   └── wallpapers/
├── Makefile
├── README.md
└── build/
```

Additional modules will be introduced when they are needed.

## Build Requirements

* Windows 11
* MSYS2 with the UCRT64 environment
* GCC / G++
* GNU Make
* raylib and its required dependencies

## Building

Open the **MSYS2 UCRT64** terminal, navigate to the project directory, and run:

```bash
make
```

Run the generated executable using the output path configured in the Makefile.

> Build instructions will be updated when the initial Makefile and source files are implemented and tested.

## Development Roadmap

* [ ] **v0.1 — Desktop Foundation:** application window, desktop background, and basic rendering.
* [ ] **v0.2 — Desktop UI:** taskbar, clock, and Start menu.
* [ ] **v0.3 — Window Manager:** multiple windows and window controls.
* [ ] **v0.4 — Terminal:** command parsing and built-in commands.
* [ ] **v0.5 — File Manager:** directory browsing and file operations.
* [ ] **v0.6 — Settings:** appearance and application configuration.
* [ ] **v1.0 — Integrated Desktop:** integrate, test, and refine the core components.

Versions and features may change as development progresses.

## Development Principles

1. Implement real functionality instead of placeholder implementations.
2. Keep modules separated and responsibilities clear.
3. Compile and test each module before proceeding.
4. Use comments where they help explain implementation details.
5. Keep the project buildable throughout development.
6. Document known limitations and update this README as the project evolves.

## Scope and Limitations

NanoOS runs as an application on Windows. It does not replace Windows, boot independently, or provide its own kernel or hardware drivers.

The desktop, internal windows, terminal, and built-in applications are intended to be implemented by the NanoOS project itself.

## License

No license has been selected yet.
Have Fun!!
----Nguyen Thanh An---- from VietNam
