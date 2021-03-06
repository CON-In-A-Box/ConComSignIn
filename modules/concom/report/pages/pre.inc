<?php

/*.
    require_module 'standard';
.*/

require_once($BACKEND."/RBAC.inc");

if (!\ciab\RBAC::havePermission("concom.reports")) {
    goSite();
}

require_once __DIR__.'/../../functions/concom.inc';
require_once($FUNCTIONDIR."/reports.inc");

$reports = [];

$sql = 'SELECT * FROM `Events`';
$result = \DB::Run($sql);
$value = $result->fetch();
while ($value !== false) {
    $reports['ConCom Membership for '.$value['EventName']] = [
    'concom_report',
    $value['EventID']
    ];
    $value = $result->fetch();
}

handle_report_request($reports);
