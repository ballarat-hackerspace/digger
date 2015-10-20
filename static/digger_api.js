/**
 * Created by rob on 31/07/15.
 */


var api_endpoint = "/api/";

var most_recent_error = null;

function perform_action(action){
    add_log_entry("Try", action);
    var data = {
        auth_token: $("#auth_token").val(),
        device_id: $("#device_id").val()
    };
    console.log(data);
    var request = $.ajax({
        url: api_endpoint + action,
        success: function(result){
            add_log_entry("Success!", result['response']);
        },
        error: function(result){
            add_log_entry("Failure!", "(see console: var most_recent_error)");
            console.log(result);
            most_recent_error = result;
        },
        data: data,
        method: 'POST',
        type: "POST"
    });
    console.log(request);
}


function add_log_entry(event_type, message){
    var s_code = "<li>" + event_type + ": " + message + "</li>";
    $("#command_log #actions").append(s_code);
}