
#pragma once

#include "Debug.h"

void showMessageBox(const juce::String& message) {
#ifdef PRINT_DEBUG_INFORMATION
  // Create a Message box window object with a title and message
  juce::AlertWindow::showMessageBox(
    juce::AlertWindow::InfoIcon,
    "Message",
    message,
    "OK"
  );
#endif
}

void printToConsole(const juce::String& message) {
#ifdef PRINT_DEBUG_INFORMATION
  // Print the message to the console
  std::cout << message << std::endl;
#endif
}
