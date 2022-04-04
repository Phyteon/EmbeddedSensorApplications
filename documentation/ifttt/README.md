# IFTTT - If This Then That

It is a service that aims to integrate apps, devices and other services. It provides a way to create applets that can perform pretty much any action user desires. Setup is very easy and for limited usage, free. For more details, please visit [the official website](https://ifttt.com/explore/new_to_ifttt "WTF is IFTTT?").

# How is it utilised in this project?

A simple applet was created in IFTTT. It is set up to be triggered by webhook event, which will be sent by ThingHTTP as an reaction to event that occured in a channel. Very little setup is needed, and example on how to do that can be found [here](https://www.mathworks.com/help/thingspeak/use-ifttt-to-send-text-message-notification.html "ThingHTTP and IFTTT setup example."). More on ThingHTTP, ThingSpeak and their usage in this project can be found [here](documentation/thingspeak/README.md "ThingSpeak purpose & setup."). 