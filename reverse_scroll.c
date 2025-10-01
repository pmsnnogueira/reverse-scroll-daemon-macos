#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDLib.h>
#include <stdio.h>

bool isTrackpad(CGEventRef event) {
    int64_t continuous = CGEventGetIntegerValueField(event, kCGScrollWheelEventIsContinuous);
    return continuous != 0;
}

CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type != kCGEventScrollWheel) return event;

    int64_t deltaY = CGEventGetIntegerValueField(event, kCGScrollWheelEventDeltaAxis1);

    if (!isTrackpad(event)) {
        CGEventSetIntegerValueField(event, kCGScrollWheelEventDeltaAxis1, -deltaY);
    }

    return event;
}

int main(void) {
    CGEventMask mask = CGEventMaskBit(kCGEventScrollWheel);

    CFMachPortRef tap = CGEventTapCreate(
        kCGHIDEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionDefault,
        mask,
        eventCallback,
        NULL
    );

    if (!tap) {
        fprintf(stderr, "Error: unable to create event tap.\n");
        return 1;
    }

    CFRunLoopSourceRef source = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, tap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), source, kCFRunLoopCommonModes);
    CGEventTapEnable(tap, true);

    printf("Scroll daemon started. Press Ctrl+C to exit.\n");
    CFRunLoopRun();

    return 0;
}
