<?php
/**
 * Include Once for initialization of elements for markup.
 */
include_once(drupal_get_path('theme', 'shoelace') . '/includes/breadcrumb.inc');
include_once(drupal_get_path('theme', 'shoelace') . '/includes/error.inc');
include_once(drupal_get_path('theme', 'shoelace') . '/includes/menu.inc');
// include_once(drupal_get_path('theme', 'shoelace') . '/includes/css.inc');

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
  /* Main Menu */
  // Get the entire main menu tree
  $mmt = menu_tree_all_data('main-menu');
  // Add the rendered output to the $main_menu_expanded variable
  $variables['main_menu_expanded'] = shoelace_dropdown_tree_output($mmt);

  // sidebars layout via Foundation markup.
  $variables['main_content_count'] = 'twelve';
  $variables['sidebar_first_content_count'] = 'four';
  $variables['sidebar_second_content_count'] = 'four';

  if ($variables['page']['sidebar_first'] || $variables['page']['sidebar_second']) {
    $variables['main_content_count'] = 'eight';
  }
  if ($variables['page']['sidebar_first'] && $variables['page']['sidebar_second']) {
    $variables['main_content_count'] = 'four';
  }
  // kpr($variables);
}

/**
 * Implementation of hook_theme().
 */
function shoelace_theme(&$existing, $type, $theme, $path) {
  // Functions provided by our theme.
  return array(
    'top_main_menu' => array(
      'render element' => 'tree',
    ),
  );
}