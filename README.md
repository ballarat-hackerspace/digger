# Autonomous Digger Project

1. Cut the control cord to a toy digger
2. Put a spark core in the middle
3. Write a wrapper API to let you control it via the internet.

This project handles the code for controlling the toy digger via the internet.
Details and controllable code to come.


# Steps to run:

1. Call curl https://api.particle.io/oauth/token -u particle:particle -d grant_type=password -d username=spark@ballarathackerspace.org.au -d password=<PASSWORD>
with the appropriate password to get an auth token

2. Go to https://ballarathackerspace.org.au/digger/
3. Enter your auth token, leave the device id alone
4. Press buttons, but ensure the digger has enough space. It needs at least 1m each way to not hit anything
