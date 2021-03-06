<?php
/*.
      require_module 'standard';
.*/

require_once(__DIR__."/../../functions/ATTENDANCE.inc");

// Sign in this user for today's meeting

if (!empty($_REQUEST['meeting'])) {
    $arguments = [
    'meeting'          => FILTER_SANITIZE_NUMBER_INT,
    ];

    $updateData = filter_input_array(INPUT_GET, $arguments);
    if (isset($updateData['meeting'])) {
        update_meeting_attendance($updateData['meeting'], $_SESSION['accountId']);
    }
}

goSite();
