# reverse-scroll-daemon-macos

A lightweight macOS daemon that enables **natural scrolling on the trackpad** and **inverted scrolling on any mouse**. Works invisibly in the background and starts automatically on login.

---

## Features

- **Trackpad**: Natural scroll (no change)  
- **Mouse** (any type): Inverted scroll  
- Runs as a lightweight daemon using macOS Event Tap  
- Automatic startup on login via LaunchAgent  
- No GUI required, minimal dependencies  

---

## Repository Structure

```
reverse-scroll-daemon-macos/
├── reverse_scroll.c          # C daemon source code
├── setup.sh                  # Setup script to compile and install daemon
└── README.md                 # Documentation
```

---

## Requirements

- **macOS 26.01**  
- **clang 17.0.0**
- **Accessibility permission** (required to intercept scroll events)

### Optional (for development/testing)
- Terminal access to compile/run C code

---

## Installation / Setup

### 1. Clone the repository
```bash
git clone https://github.com/yourusername/scroll-reverse-daemon.git
cd scroll-reverse-daemon
```

### 2. Make the setup script executable
```bash
chmod +x setup.sh
```

### 3. Run the setup script
```bash
./setup.sh
```

This will:
- Compile the daemon
- Create a LaunchAgent
- Load it automatically

The daemon will now run at login and in the background.

### 4. Grant Accessibility permission
1. Open **System Settings** → **Privacy & Security** → **Accessibility**
2. Add the compiled binary (`reverse_scroll.out`) to allow it to intercept scroll events

---

## Running Manually (for Developers / Testing)

compile the c file
```bash
clang -framework ApplicationServices -framework CoreFoundation reverse_scroll.c -o reverse_scroll.out
```

You can run the daemon directly in terminal:

```bash
./reverse_scroll
```

- Press **Ctrl+C** to stop the daemon

---

## Development Notes

- The daemon intercepts all scroll events via `CGEventTap`
- Trackpads are detected via the `kCGScrollWheelEventIsContinuous` property
- Mouse events (non-continuous) are inverted automatically

---

## Updating / Recompiling

1. Edit `reverse_scroll.c` as needed
2. Re-run the setup script:
   ```bash
   ./setup.sh
   ```

This will recompile and reload the LaunchAgent automatically.

---

## Uninstall

To stop and remove the daemon:

```bash
launchctl unload ~/Library/LaunchAgents/com.user.scrollreverse.plist
rm ~/Library/LaunchAgents/com.user.scrollreverse.plist
rm reverse_scroll
```

---

## Notes

- Minimal dependencies, purely in C
- Lightweight and invisible, no GUI
- Can be used alongside other input modification tools, but only one daemon should handle scroll inversion to avoid conflicts

---

## License

MIT License - feel free to use and modify as needed.

---

## Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

---