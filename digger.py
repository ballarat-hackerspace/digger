from requests import post
from flask import Flask, send_from_directory, abort, jsonify
from flask import request

app = Flask(__name__)

@app.route('/')
def hello_world():
    return app.send_static_file('control.html')


@app.route("/bootstrap/<path:path>")
def serve_bootstrap(path):
    return send_from_directory('static/bootstrap', path)


#TODO These should correlate to functions on the particle core.
# First argument is the function name, second is the arguments to pass
valid_actions = {}
valid_actions["forwards"] = ("motor_running_function", "MOTOR 0 forwards; MOTOR 1 forwards")
valid_actions["backwards"] = ("motor_running_function", "MOTOR 0 backwards; MOTOR 1 backwards")
valid_actions["left"] = ("motor_running_function", "MOTOR 0 forwards; MOTOR 1 backwards")
valid_actions["right"] = ("motor_running_function", "MOTOR 0 backwards; MOTOR 1 forwards")

valid_actions["clockwise"] = ("motor_running_function", "MOTOR 2 forwards")
valid_actions["anticlockwise"] = ("motor_running_function", "MOTOR 2 backwards")

valid_actions["arm_up"] = ("motor_running_function", "MOTOR 3 forwards")
valid_actions["arm_down"] = ("motor_running_function", "MOTOR 3 backwards")

valid_actions["bucket_in"] = ("motor_running_function", "MOTOR 4 forwards")
valid_actions["bucket_out"] = ("motor_running_function", "MOTOR 4 backwards")

valid_actions["stop"] = ("motor_running_function", "MOTOR * stop")

# API Format for calling a function: https://api.spark.io/v1/devices/<DEVICEID>/<FUNCTION>
function_api = "https://api.spark.io/v1/devices/{device_id}/{function}"

core_running = False  # Set to True when the core is running -- otherwise API calls aren't actually made!

#TODO Should be POST, and this should be secured anyway with HTTPS

@app.route("/api/<action>", methods = ['POST', "GET"])
def do_action(action):
    app.logger.error(request.form)
    #if not "auth_token" in request.form:
    #    return abort(403)
    auth_token = request.form.get('auth_token', "no auth")
    device_id = request.form.get('device_id', "no device")
    if action not in valid_actions:
        abort(404)

    function_name, function_args = valid_actions[action]
    api_url = function_api.format(device_id=device_id, function=function_name)

    payload = {}
    payload['access_token'] = auth_token
    payload['arg'] = function_args

    #TODO: Make request here
    if core_running:
        post(api_url, data=payload)

    #TODO: Return status based on whether this worked or not
    f = {"status": "success", "action": action,
         "message": api_url + ", payload: {}".format(payload)}
    return jsonify(**f)


if __name__ == '__main__':
    #if not app.debug:
    #    import logging
    #    handler = logging.FileHandler("output.log")
    #    handler.setLevel(logging.DEBUG)
    #    app.logger.addHandler(handler)
    app.run(use_debugger=False, use_reloader=False, debug=True)
    #app.run(debug=True)
