<?php

/*.
    require_module 'standard';
    require_module 'json';
.*/

/* This should only be accessable from volunteer staff */
if (!(isset($_SESSION['IS_ADMIN']) || $_SESSION['IS_VOLUNTEERS'])) {
    goSite();
}

require_once($FUNCTIONDIR."/volunteer.inc");

$response = array();

$file = fopen('php://input', 'r');
$lineno = 0;
while (!feof($file)) {
    $data = fgets($file);
    $lineno++;
    if ($data == false) {
        break;
    }
    $data = trim($data);
    $csv = str_getcsv($data);
    if (count($csv) === 9) {
        array_shift($csv);
    }
    if ($csv == null || $csv == false || count($csv) != 8) {
        $response[] = strval($lineno).': malformed: '.strval($data);
    } else {
        $event = null;
        if ($csv[6]) {
            $event = $csv[6];
        }
        if (is_numeric($csv[3])) {
            $csv[3] = intval($csv[3]);
        }
        /* user lookups */
        $user = null;
        $output = lookup_users_by_key($csv[0]);
        if (count($output['users']) != 1) {
            $response[] = strval($lineno).': failed: '.strval($data).': Unable to lookup user.';
            continue;
        }
        $user = $output['users'][0]['Id'];

        $output = lookup_users_by_key($csv[2]);
        if (count($output['users']) != 1) {
            $response[] = strval($lineno).': failed: '.strval($data).' : Unable to lookup authorizer.';
            continue;
        }
        $authorizer = $output['users'][0]['Id'];

        $output = lookup_users_by_key($csv[5]);
        if (count($output['users']) != 1) {
            $response[] = strval($lineno).': failed: '.strval($data).' : Unable to lookup enterer.';
            continue;
        }
        $enterer = $output['users'][0]['Id'];

        $overlap = find_overlap_hours($csv[4], $csv[1], $user);
        if ($overlap != null) {
            $response[] = strval($lineno).': overlap: '.strval($data).' : Hours Overlap with existing hours.';
            continue;
        }

        try {
            $result = record_volunteer_hours(
                $user,
                $csv[1],
                $csv[4],
                $csv[7],
                $csv[3],
                $enterer,
                $authorizer,
                $event
            );
            $response[] = strval($lineno).': success: '.strval($data);
        } catch (Exception $e) {
            $response[] = strval($lineno).': failed: '.strval($data).' : '.$e->getMessage();
        }
    }
}
fclose($file);

echo json_encode($response);
exit();