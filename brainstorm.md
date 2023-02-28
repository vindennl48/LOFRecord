# LOF Recording Plugin

## Features

### Definite
- When we STOP recording, we want some sort of popup window confirming that we
  want to stop recording.. we do NOT want to accidentally stop recording..
- Check to see what happens to the recordings / instances when the audio device
  is disconnected or changed? ( i know ableton crashes on disconnect, but if i
  change the inputs/outputs, does it affect anything? )
- Might want to start looking into multithreading and having the audio save in a
  different thread like the docs tell us to do :|
- Have each instance's data be saved in a static variable or data-store.  Then
  all instances can access everyone elses data.
  - Want to change the user interface to have the following
    - Have a tab that defaults to the Instances page
      - Record button at the top for the current instance (and any other instance
        in the same group)
      - Big excel table to list all the currenty opened instances, with the
        following columns:
        - Track Name, Group Name (song name), Recording, Start on Launch, Start on Playback
        - Always show the current instance at the top of the list
      - Need to figure out how to do vertical scroll bars
    - Have a Tab that lets us go to the recorded page
      - Need some sort of refresh button or way to refresh this view
      - Lists out all of the recordings by group in chronological order. (ie.
        doesnt show every track from a group, just the group as a whole).  This
        allows you to drag and drop directly into the timeline.
      - Need to figure out how to do vertical scroll bars
      - Columns:
        - Date(drag), Time(drag), Group(editable), Count, Listen, Delete
        - During Group(editable) edit, turn box red and dont save until the user
          clicks enter or goes outside of the box.  If the user presses ESC,
          then cancel the request and reset the box to the original name.
        - (drag) just means the audio is draggable from those fields
        - Delete button just moves into a temp folder in case we do it by
          accident, should also come up with a dialog box to confirm.
        - Listen button takes us to a hidden tab to listen back to the audio
    - Have a hidden tab to listen to the selected group recordings
      - List out audio clip waveforms from the specific time and group
      - Click on a section of the waveform to play-back from, this should play
        all the stems together
      - Add two buttons to each track for solo and mute
      - These should be draggable as well
      - Add Back, Date, Time, Group(editable), Count, and Delete options at the top

### Second Pass
- Possibly figure out if we can record straight to MP3 instead of wav

### Dreams
- Having some sort of command-center view where you can see all of the open
  instances in the DAW.
  - Let you control all instances, rename, start/stop, etc. from one plugin
    view.
- Be able to drag-drop previously recorded clips from plugin window to the DAW
  timeline.  (yes this is supposedly possible)
- Especially for the long practice recordings, it would be massively beneficial
  to be able to see the waveform and chop out clips from a bigger recording.
  especially as it's recording.
- Auto-pull the track name from the DAW to set as the track name
  - As of right now, it has to be manually typed in, has benefits and drawbacks
- Some way of auto-starting the recording process just in case i forget?
  - Maybe have some sort of popup window to ask if we want to start recording
- Show a list of all of the plugin instances.  Set which ones we want to be
  recording, and just gives us an idea of how many we have open.
  - There is apparently a way to show wav-forms if we wanted to do playback..
- 

### Done
- Global start and stop recording
- Set a directory instead of a file to save to
- Grab the current date ( and possibly ms time ) to append to the filename
  - Make sure that the date/time is global to ALL plugin instances, want each
    recording to be synced in some fassion.
- Be able to give a song_name to all the plugin instances
- Auto-increment when saving, do NOT overwrite
- Give a name to concat with the date to save in the specified directory
  - or ask for the track name?  Not sure if JUCE can auto do this or not
    - (future me here: Apparently there is a way to do it..)
- Basically for the naming convention we want this:
  - Date and Time:      230223_123456
  - Directory Location: /Users/mitch/Desktop/
  - Song Name:          Slough part 1
  - Track Names:        Mitch
  - Output: /Users/mitch/Desktop/230223-123456-Slough_part_1-Mitch-000.wav
    directory-date-time-song_name-track_name-count.wav
- Have a checkbox to start recording at startup (for recording the full practice)


## What We Want Out of Ableton
- custom clicks
- talkback
- fip easily between multiple setups
  - Live Shows
  - Practice / Jams
  - Working on new songs
  - Elephant shizz
- Backtrack ability if someone is not at practice
- Save projects outside of the main project for space savings
- One track input per person that sums up everything that plays
