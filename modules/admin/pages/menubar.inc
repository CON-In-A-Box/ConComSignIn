<?php
if (isset($_SESSION['IS_ADMIN'])) {
    $admin_menus[] = array('base style' => 'w3-yellow',
     'selected style' => 'w3-green',
     'function' => 'admin',
     'title' => 'Oh the administration',
     'i class' => 'fa fa-key',
     'text' => 'Administration',
     'responsive' => true);
}