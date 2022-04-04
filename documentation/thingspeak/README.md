# ThingSpeak - what is it?

ThingSpeak is an IoT analytics platform service that allows you to aggregate, visualize and analyze live data streams in the cloud. ThingSpeak provides instant visualizations of data posted by your devices to ThingSpeak. With the ability to execute MATLAB code in ThingSpeak you can perform online analysis and processing of the data as it comes in. ThingSpeak is often used for prototyping and proof of concept IoT systems that require analytics. More details [on the offical website](https://thingspeak.com/pages/learn_more "Official ThingSpeak website.").

# ThingHTTP

ThingHTTP enables communication among devices, websites, and web services without having to implement the protocol on the device level. You specify actions in ThingHTTP, which you trigger using other ThingSpeak apps such as TweetControl, TimeControl, and React.

# How is it used in this project?

It is the basis for remote monitoring of parameters measured by the sensing element. Using this service allows for much simpler project infrastructure and system architecture. The microcontroller in the sensing element will send data through the ThingSpeak channel to the cloud, where all the necessary processing will take place, such as simple conversion, but also filtering (and if time allows, then maybe even some predictions). The effect of the processing will decide what action will be taken, or no action at all.