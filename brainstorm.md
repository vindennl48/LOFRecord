# LOF Recording Plugin

## Features

### Definite
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

### Second Pass
- Possibly figure out if we can record straight to MP3 instead of wav

### Dreams
- Some way of auto-starting the recording process just in case i forget?
  - Maybe have some sort of popup window to ask if we want to start recording
- Show a list of all of the plugin instances.  Set which ones we want to be
  recording, and just gives us an idea of how many we have open.
  - There is apparently a way to show wav-forms if we wanted to do playback..
- 
