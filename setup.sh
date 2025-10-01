#!/bin/bash

DIR="$(pwd)"
BIN="$DIR/scroll_reverse"
OUT="$BIN.out"

# Compile the daemon
echo "Compiling scroll_reverse..."
clang -framework ApplicationServices -framework CoreFoundation scroll_reverse.c -o "$OUT"

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compiled successfully: $OUT"

# Create LaunchAgents directory if not exists
mkdir -p ~/Library/LaunchAgents

# Create plist
PLIST=~/Library/LaunchAgents/com.user.scrollreverse.plist

cat > "$PLIST" <<EOL
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" 
"http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>com.user.scrollreverse</string>
    <key>ProgramArguments</key>
    <array>
        <string>$OUT</string>
    </array>
    <key>RunAtLoad</key>
    <true/>
    <key>KeepAlive</key>
    <true/>
</dict>
</plist>
EOL

echo "LaunchAgent plist created at $PLIST"

# Reload the LaunchAgent (applies immediately)
launchctl unload "$PLIST" 2>/dev/null
launchctl load "$PLIST"

echo "LaunchAgent loaded. Scroll daemon is running now and will start on login."
echo "IMPORTANT: Add $OUT to System Settings → Privacy & Security → Accessibility."
