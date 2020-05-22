# Alexa - Elgato Keylight
Elgato Keylight's integration with Alexa using ESP8266.

### Dependencies
In order to compile this piece of software, you'll need all **libraries provided by ESP8266** with the Arduino's IDE Board Manager adding the following URL to preferences of the IDE:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
And then selecting the Board Model under Tools (i.e. NodeMCU 0.9/NodeMCU 1.0, etc.)

You'll also need **@Aircoookie 's Espalexa library**: https://github.com/Aircoookie/Espalexa
You can import it just by downloading his repo as a Zip, then going to Program -> Add library and selecting it.

### Configuration
First of all, you'll need data from your Keylight such as the *IP address*, *port* it's using *(should be 9123)* and the *number of lights*.
You will configure those three things changing the constants:
**keylight_ip** => String "192.168.1.xxx"
**keylight_port** => int 9123
**keylight_number_of_lights** => int 1/2/3...

Then you'll need to set your Wi-Fi settings, should be the same one where the device is connected to; by changing those constants:
**wifi_ssid** => String "YOUR_SSID_HERE"
**wifi_password** => String "YOUR_PASS_HERE"

Bare in mind that if your router is assigning the IP to the Keylight via DHCP, it's strongly recommended to discover the **MAC Address** of your keylight (can be done in most of routers) and configure it to assign the light an static IP so you don't have to re-compile this program each time.

### Future of this project
As of now, Elgato haven't pronounced about making their own Alexa skill to integrate it with the Keylight, and it's not probable it'll happen.
If not, one thing I want to do is a web interface to manage and discover the Keylights available, so you don't have to hardcode the IP Address.

In the next release, I'll implement the color temperature adjustment too, as it's allowed by the library we are using.

### Contributing
I only have one Elgato Keylight, so I cannot test how does it work with multiple lights. As soon as I have access to some friend's set-up to try it, I will, if necessary, update this project to make it work (it should work now anyway).
If you are fortunate of having two and you test it, a commit is welcome.

### Donations
If you want to help me doing more projects, you can donate here: http://paypal.me/maduranma