# LOF Recording Plugin

## TODO
- when creating a new instance, make sure that the track name is unique

- Really need to add a way we can change the entire group name instead of having
  to do one at a time.  when changing between songs at practice, it would be
  very helpful to only have to do it once.
  - Maybe a button with a popup to type in instead?

- Need to add tabs back in

- Would be nice to be able to re-arrange the order of the instances.
  - Could probably do this by moving them around inside the insts array.

- Disable all text input and button presses while recording (not that it should
  really screw with anything but it should be there)
  - probably want to wait till we fix the plugin updating first since nothing
    will auto-disable until the mouse interacts with it.

## Features

### Definite
  - Want to change the user interface to have the following
    - Have a tab that defaults to the Instances page
      - big list of all plugin instances open
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
- Set a default path for future instances
- Be able to drag-drop previously recorded clips from plugin window to the DAW
  timeline.  (yes this is supposedly possible)
- Especially for the long practice recordings, it would be massively beneficial
  to be able to see the waveform and chop out clips from a bigger recording.
  especially as it's recording.
- Auto-pull the track name from the DAW to set as the track name
  - As of right now, it has to be manually typed in, has benefits and drawbacks


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
