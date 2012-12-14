<?php

/**
 * Include Once for initialization of elements for twitter bootstrap markup,
 * look and feel.
 */
include_once(drupal_get_path('theme', 'shoelace') . '/includes/breadcrumb.inc');
include_once(drupal_get_path('theme', 'shoelace') . '/includes/error.inc');
include_once(drupal_get_path('theme', 'shoelace') . '/includes/menu.inc');
include_once(drupal_get_path('theme', 'shoelace') . '/includes/css.inc');

/**
 * Override or insert variables into the html templates.
 */
function shoelace_process_html(&$variables, $hook) {
  // Flatten out html_attributes.
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Override or insert variables into the html template.
 */
function shoelace_preprocess_html(&$variables, $hook) {
  // Add variables and paths needed for HTML5 and responsive support.
  $variables['base_path'] = base_path();
  $variables['path_to_shoelace'] = drupal_get_path('theme', 'shoelace');

  // Attributes for html element.
  $variables['html_attributes_array'] = array(
    'lang' => $variables['language']->language,
    'dir' => $variables['language']->dir,
  );
}

function shoelace_preprocess_page(&$variables) {
  // Get the entire main menu tree
  $main_menu_tree = menu_tree_all_data('main-menu');

  // Add the rendered output to the $main_menu_expanded variable
  $variables['main_menu_expanded'] = shoelace_tree_output($main_menu_tree);
}