<?php

function shoelace_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  /* additioanl array to change the class for zurb styling */
  $status_type = array(
    'status' => 'success', 
    'error' => 'alert', 
    'warning' => 'secondary',
  );

  $status_heading = array(
    'status' => t('Status message'), 
    'error' => t('Error message'), 
    'warning' => t('Warning message'),
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    /* passing the new change here */
    $output .= "<div class=\"alert-box $status_type[$type]\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}