node-red-contrib-ibm-watson-iot
===============================

A pair of Node-RED nodes for connecting to the IBM Watson Internet of Things Platform
as a Device or Gateway.

## Install

Run the following command in the user directory of your Node-RED install. This is
usually ``~/.node-red`.

```
npm install node-red-contrib-ibm-watson-iot
```
----

Supported Features
------------------

| Feature   |      Supported?      | Description |
|----------|:-------------:|:-------------|
| [Device connectivity](https://console.ng.bluemix.net/docs/services/IoT/applications/dev_nodered.html) |  &#10004; | Connect your device(s) to Watson IoT Platform with ease using this library. [Click here](https://developer.ibm.com/recipes/tutorials/getting-started-with-watson-iot-platform-using-node-red/) for detailed information on how devices can publish events and handle commands.|
| [Gateway connectivity](https://console.ng.bluemix.net/docs/services/IoT/applications/dev_nodered.html) |    &#10004;   | Connect your gateway(s) to Watson IoT Platform with ease using this library. [Click here](https://developer.ibm.com/recipes/tutorials/getting-started-with-watson-iot-platform-using-node-red/) for detailed information on how gateways can publish events and handle commands for itself and for the attached devices. |
| [SSL/TLS support](https://console.ng.bluemix.net/docs/services/IoT/reference/security/index.html) | &#10004; | By default, this library connects your devices, gateways and applications **securely** to Watson IoT Platform registered service. Ports 8883(default one) and 443 support secure connections using TLS with the MQTT and HTTP protocol. Also, note that the library uses port 1883(unsecured) to connect to the Quickstart service.|
| [Client side Certificate based authentication](https://console.ng.bluemix.net/docs/services/IoT/reference/security/RM_security.html) | &#10004; | Default connections between devices and the platform use either the Certificates Only or Certificates with Authentication Tokens security levels.|
| [Auto reconnect](https://github.com/eclipse/paho.mqtt.java/issues/9) | &#10004; | Enables device and gateway to automatically reconnect to Watson IoT Platform while they are in a disconnected state. [Further details here](https://console.ng.bluemix.net/docs/services/IoT/devices/libraries/nodejs.html#connecting_to_iotp). |
| [Multi-format support](https://github.com/amprasanna/node-red-contrib-ibm-watson-iot)| &#10004; | The format of the event defaults to JSON, but can be set to another value or, if left blank, can be set by the msg.format property. |


Supported Features
------------------

| Feature   |      Supported?      | Description |
|----------|:-------------:|:-------------|
| [Device Management](https://console.ng.bluemix.net/docs/services/IoT/devices/device_mgmt/index.html) | &#10008; | Currently not supported.|
| Websocket | &#10008; | Currently not supported. |


----

## Usage

### Input Node

The input node receive device commands from the IBM Watson Internet of Things Platform.

The node can connect as either a Device or Gateway:

  - **Device**: the node can be configured to either receive all commands for
      the Device, or just select a specific command type.
  - **Gateway**: the node can be configured to receive commands for all devices
      connected through the gateway, or to select a subset of them.

The message sent by this node will include the following properties:

   - `payload` - the body of the command. If the command was identified as json,
    this property will be a JavaScript object, otherwise it will be a string.
   - `topic` - the topic the command was received on
   - `command` - the command name
   - `format` - the format of the command
   - `deviceType` - (*gateway only*) the type of device the command is for
   - `deviceId` - (*gateway only*) the id of the device the command is for


### Output Node

Send device events to the IBM Watson Internet of Things Platform.

The node can connect as either a Device or Gateway, in registered mode or using
the Quickstart service.

When connecting using the Quickstart service, the connection will use a device
type of `node-red-ibmwiotp` and a randomly generated device id, which can be
configured in the node. The events from the node can then be viewed on the [Quickstart dashboard](https://quickstart.internetofthings.ibmcloud.com/).

The type of the event sent can be configured in the node or, if left blank, can
be set by the `msg.event` property.

The format of the event defaults to `json`, but can be set to another value or,
if left blank, can be set by the `msg.format` property.

The data for the event is taken from `msg.payload`. If `format` is set to `json`,
this node will attempt to encode the data appropriately:

  - If the data is an Object of the form: `{ d: { ... }}` it will be used as-is.
    Similarly if it is a string representation of such an object no further
    encoding will be done.
  - For any other type of object, for example a Number, it will be sent as `{"d":{"value":123}}`

If `format` is set to anything else, the data will be passed on as-is.

When connected as a Gateway, the type and id of the Device the event is being
sent on behalf of can be configured in the node or, if left blank, can be set by
the `msg.deviceType` and `msg.deviceId` properties. If these properties are not
provided, either in the node or the message, it will use the type and id of the
Gateway itself.

=======
