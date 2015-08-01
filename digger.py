from flask import Flask, send_from_directory, abort, jsonify

app = Flask(__name__)

@app.route('/')
def hello_world():
    return app.send_static_file('control.html')


@app.route("/bootstrap/<path:path>")
def serve_bootstrap(path):
    return send_from_directory('static/bootstrap', path)


#TODO These should correlate to Spark Endpoints
valid_actions = {}
valid_actions["forwards"] = "MOTOR 0 forwards; MOTOR 1 forwards"
valid_actions["backwards"] = "MOTOR 0 backwards; MOTOR 1 backwards"
valid_actions["left"] = "MOTOR 0 forwards; MOTOR 1 backwards"
valid_actions["right"] = "MOTOR 0 backwards; MOTOR 1 forwards"

valid_actions["clockwise"] = "MOTOR 2 forwards"
valid_actions["anticlockwise"] = "MOTOR 2 backwards"

valid_actions["arm_up"] = "MOTOR 3 forwards"
valid_actions["arm_down"] = "MOTOR 3 backwards"

valid_actions["bucket_in"] = "MOTOR 4 forwards"
valid_actions["bucket_out"] = "MOTOR 4 backwards"

valid_actions["stop"] = "MOTOR * stop"


@app.route("/api/<action>")
def do_action(action):
    if action in valid_actions:
        f = {"status": "success", "action": action,
             "message": valid_actions[action]}
        return jsonify(**f)
    else:
        return abort(404)


if __name__ == '__main__':
    app.run(use_debugger=False, use_reloader=False)
