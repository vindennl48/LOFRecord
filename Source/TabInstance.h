#pragma once

#include <JuceHeader.h>

using namespace juce;

class TableComponent  : public Component,
                        private TableListBoxModel
{
public:
    TableComponent ()
    {
        addAndMakeVisible (table);

        table.setModel (this);
        table.setClickingTogglesRowSelection (false);
        table.setHeader ([&]
        {
            auto header = std::make_unique<TableHeaderComponent>();
            header->addColumn ("Track",           trackColumn,         120, 30, -1, TableHeaderComponent::notSortable);
            header->addColumn ("Group",           groupColumn,         120, 30, -1, TableHeaderComponent::notSortable);
            header->addColumn ("Recording",       recordingColumn,     120, 30, -1, TableHeaderComponent::notSortable);
            header->addColumn ("Start on Launch", startOnLaunchColumn, 120, 30, -1, TableHeaderComponent::notSortable);
            header->addColumn ("Start on Play",   startOnPlayColumn,   120, 30, -1, TableHeaderComponent::notSortable);
            return header;
        }());
    }

    void resized() override { table.setBounds (getLocalBounds()); }

private:
    enum
    {
        trackColumn = 1,
        groupColumn,
        recordingColumn,
        startOnLaunchColumn,
        startOnPlayColumn
    };

    int getNumRows() override          { return (int) 10; }

    void paintRowBackground (Graphics&, int, int, int, bool) override {}
    void paintCell (Graphics&, int, int, int, int, bool)     override {}

    Component* refreshComponentForCell (
      int rowNumber,
      int columnId,
      bool,
      Component* existingComponentToUpdate) override
    {
        delete existingComponentToUpdate;

        return new Label ({}, [&]
        {
            switch (columnId)
            {
                case trackColumn:         return String("track");
                case groupColumn:         return String("group");
                case recordingColumn:     return String("is recording");
                case startOnLaunchColumn: return String("yes");
                case startOnPlayColumn:   return String("no");
                default: break;
            }

            jassertfalse;
            return String();
        }());
    }

    TableListBox table;
};



class TabInstance : public juce::Component {
public:
  TabInstance() {
    addAndMakeVisible(table);
  }

  void paint(juce::Graphics& g) override {
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    // g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
  }

  /**
  * Set size, position, and font of comopnents
  */
  void resized() override {
    table.setBounds(getLocalBounds());
  }

private:
  // juce::Label titleLabel {"instanceName", "Default"};
  TableComponent table;
};
