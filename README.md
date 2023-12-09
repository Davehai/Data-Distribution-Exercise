# Data-Distribution-Exercise

v0.0
This Exercise is using two main parts:
# Server:
That contains a publisher udp listener and udp raii
  The publisher uses the udp listener to receive requests to subscribeand to it.
  The publisher holds a udp raii to notify the subscribers about about the state of the shapes they requested.
  The udp listener uses an udp raii to get requests to subscribe to the publisher.
  The udp raii is used to initialize a udp fd and store the sockets data.
# Server notes:
  To subscribe to the server you need to sand a string in a format request/shape/ip/port via udp.
  *request may be subscribe or unsubscribe.
  *shape may be a specific shape or all if you want to get notify on all shapes.
  To run the server test run make -f makefile.server
    In the server test the server listens on ip 127.0.0.1 port 4000 and replise on ip 127.0.0.1 port 8080.
    The server isnt complited and only sands strings where the first word is the shape key.

# Subscriber:
The subscriber is a class that in this case uses udp raii as well to start a fd that listens to messages from the server.
# Subscriber notes:
  To initialize a subscriber you need to sand it a string to be the ip and an int for the port (there is no default ctor).
  To subscribe to a server you need to call the Subscribe member function and send the if port and shape you want to subscribe.
  To unsubscribe to a server you need to call the UnSubscribe member function.
  To run the subscriber test run make if makefile.subscriber.
  
  
