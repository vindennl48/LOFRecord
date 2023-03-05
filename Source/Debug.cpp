
#pragma once

#include "Debug.h"

void showMessageBox(const juce::String& message) {
  // Create a Message box window object with a title and message
  juce::AlertWindow::showMessageBox(
    juce::AlertWindow::InfoIcon,
    "Message",
    message,
    "OK"
  );
}
