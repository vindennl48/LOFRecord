
#include <JuceHeader.h>
#include "TabInstance.h"
#include "PluginEditor.h"



// TabInstanceTable::TabInstanceTable() {
//   addAndMakeVisible(table);
//   table.setModel(this);
//   table.setColour (ListBox::outlineColourId, Colours::grey);
//   table.setOutlineThickness (1);
//   table.getHeader().addColumn("Column 1", 1, 200, 50, 400, juce::TableHeaderComponent::defaultFlags);
//   table.getHeader().addColumn("Column 2", 2, 200, 50, 400, juce::TableHeaderComponent::defaultFlags);
//   table.getHeader().addColumn("Column 3", 3, 200, 50, 400, juce::TableHeaderComponent::defaultFlags);
//   table.setMultipleSelectionEnabled (true);
// }

// int TabInstanceTable::getNumRows() {
//   return numRows;
// }

// void TabInstanceTable::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) {
//   if (rowIsSelected)
//     g.fillAll(juce::Colours::lightblue);
// }

// void TabInstanceTable::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
//   g.setColour(getLookAndFeel().findColour (ListBox::textColourId));
//   g.setFont(14.0f);
//   // g.drawText("Cell " + juce::String(rowNumber) + "," + juce::String(columnId), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
//   g.drawText("CELL!", 2, 0, width - 4, height, Justification::centredLeft, true);
//   g.setColour(getLookAndFeel().findColour (ListBox::backgroundColourId));
//   g.fillRect(width - 1, 0, 1, height);
// }

// void resized() override
// {
//     // position our table with a gap around its edge
//     table.setBoundsInset (BorderSize<int> (8));
// }



TabInstance::TabInstance() {
  // addAndMakeVisible(titleLabel);
  // LOFRecordAudioProcessorEditor::is_recording_woo = true;
  addAndMakeVisible(table);
}

void TabInstance::paint(juce::Graphics& g) {
  g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
  // g.fillAll(juce::Colours::black);
  g.setColour (juce::Colours::white);
  g.setFont (24.0f);
}

/**
* Set size, position, and font of comopnents
*/
void TabInstance::resized() {
  // titleLabel.setBounds(0, 0, getWidth() - 40, 30);
  // titleLabel.setJustificationType(juce::Justification::left);
  // titleLabel.setFont(juce::Font(30.0f, juce::Font::bold));

  table.setBounds(getLocalBounds());
}