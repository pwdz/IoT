import time
import vlc
import serial
  
media_player = vlc.MediaPlayer()
  
# media object
media = vlc.Media("/home/pwdz/Desktop/Wrath.of.Man.2021.720p.WEB-DL.2CH.x265.HEVC-PSA.Zardfilm.Net.mkv")
  
# setting media to the media player
media_player.set_media(media)
vol = 50
state = 'pause'
  
def play():
    global state
    if state != 'play':
        state = 'play'
        media_player.play()

def pause():
    global state
    if state != 'pause':
        state = 'pause'
        media_player.pause()

def change_volume(amount):
    global vol
    vol += amount    
    media_player.audio_set_volume(vol)


play()

serial_port = serial.Serial(port = "/dev/ttyUSB0", baudrate=9600,
                           bytesize=8, timeout=5, stopbits=serial.STOPBITS_ONE) 
while True:
    if(serial_port.in_waiting > 0):
        serial_string = serial_port.readline()
        message = serial_string.decode('utf-8')
        message = message[:len(message)-1]
        print("Incoming message:", message)
        if 'play' in message:
            play()
        elif 'pause' in message:
            pause()
        elif 'increase' in message:
            change_volume(10)
        elif 'decrease' in message:
            change_volume(-10)