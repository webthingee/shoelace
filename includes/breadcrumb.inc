<?php
/**
 * Implements template_breadcrumb().
 */
function shoelace_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $title = strip_tags(drupal_get_title());

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<ul class="breadcrumbs">' . implode(' &raquo; ', $breadcrumb) . ' &raquo; ' . $title . '</ul>';
    return $output;
  }
}