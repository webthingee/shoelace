<?php
/**
 * Overrides theme_menu_tree().
 **/
function shoelace_preprocess_shoelace_sub_tree_output() {
  dsm('theme');
}
/**
 * Overrides theme_links() for system_main_menu.
 */
function shoelace_tree_output($tree) {
  $build = array();
  $items = array();

  // Pull out just the menu links we are going to render so that we
  // get an accurate count for the first/last classes.
  foreach ($tree as $data) {
    if ($data['link']['access'] && !$data['link']['hidden']) {
      $items[] = $data;
    }
  }

  $router_item = menu_get_item();
  $num_items = count($items);
  foreach ($items as $i => $data) {
    $class = array();
    if ($i == 0) {
      $class[] = 'first';
    }
    if ($i == $num_items - 1) {
      $class[] = 'last';
    }
    // Set a class for the <li>-tag. Since $data['below'] may contain local
    // tasks, only set 'expanded' class if the link also has children within
    // the current menu.
    if ($data['link']['has_children'] && $data['below']) {
      $class[] = 'has-dropdown';
    }
    elseif ($data['link']['has_children']) {
      $class[] = 'collapsed';
    }
    else {
      $class[] = 'leaf';
    }
    // Set a class if the link is in the active trail.
    if ($data['link']['in_active_trail']) {
      $class[] = 'active-trail';
      $data['link']['localized_options']['attributes']['class'][] = 'active-trail';
    }
    // Normally, l() compares the href of every link with $_GET['q'] and sets
    // the active class accordingly. But local tasks do not appear in menu
    // trees, so if the current path is a local task, and this link is its
    // tab root, then we have to set the class manually.
    if ($data['link']['href'] == $router_item['tab_root_href'] && $data['link']['href'] != $_GET['q']) {
      $data['link']['localized_options']['attributes']['class'][] = 'active';
    }

    // Allow menu-specific theme overrides.
    $element['#theme'] = 'menu_link__' . strtr($data['link']['menu_name'], '-', '_');
    $element['#attributes']['class'] = $class;
    $element['#title'] = $data['link']['title'];
    $element['#href'] = $data['link']['href'];
    $element['#localized_options'] = !empty($data['link']['localized_options']) ? $data['link']['localized_options'] : array();
    $element['#below'] = $data['below'] ? shoelace_sub_tree_output($data['below']) : $data['below'];
    $element['#original_link'] = $data['link'];
    // Index using the link's unique mlid.
    $build[$data['link']['mlid']] = $element;
  }
  if ($build) {
    // Make sure drupal_render() does not re-order the links.
    $build['#sorted'] = TRUE;
    // Add the theme wrapper for outer markup.
    // Allow menu-specific theme overrides.
    // $build['#theme_wrappers'][] = 'menu_tree__' . strtr($data['link']['menu_name'], '-', '_');
  }

  return $build;
}

/**
 * Overrides theme_links() for system_main_menu.
 */
function shoelace_sub_tree_output($tree) {
  $build = array();
  $items = array();

  // Pull out just the menu links we are going to render so that we
  // get an accurate count for the first/last classes.
  foreach ($tree as $data) {
    if ($data['link']['access'] && !$data['link']['hidden']) {
      $items[] = $data;
    }
  }

  $router_item = menu_get_item();
  $num_items = count($items);
  foreach ($items as $i => $data) {
    $class = array();
    if ($i == 0) {
      $class[] = 'first';
    }
    if ($i == $num_items - 1) {
      $class[] = 'last';
    }
    // Set a class for the <li>-tag. Since $data['below'] may contain local
    // tasks, only set 'expanded' class if the link also has children within
    // the current menu.
    if ($data['link']['has_children'] && $data['below']) {
      $class[] = 'has-dropdown';
    }
    elseif ($data['link']['has_children']) {
      $class[] = 'collapsed';
    }
    else {
      $class[] = 'leaf';
    }
    // Set a class if the link is in the active trail.
    if ($data['link']['in_active_trail']) {
      $class[] = 'active-trail';
      $data['link']['localized_options']['attributes']['class'][] = 'active-trail';
    }
    // Normally, l() compares the href of every link with $_GET['q'] and sets
    // the active class accordingly. But local tasks do not appear in menu
    // trees, so if the current path is a local task, and this link is its
    // tab root, then we have to set the class manually.
    if ($data['link']['href'] == $router_item['tab_root_href'] && $data['link']['href'] != $_GET['q']) {
      $data['link']['localized_options']['attributes']['class'][] = 'active';
    }

    // Allow menu-specific theme overrides.
    $element['#theme'] = 'menu_link__' . strtr($data['link']['menu_name'], '-', '_');
    $element['#attributes']['class'] = $class;
    $element['#title'] = $data['link']['title'];
    $element['#href'] = $data['link']['href'];
    $element['#localized_options'] = !empty($data['link']['localized_options']) ? $data['link']['localized_options'] : array();
    $element['#below'] = $data['below'] ? shoelace_sub_tree_output($data['below']) : $data['below'];
    $element['#original_link'] = $data['link'];
    // Index using the link's unique mlid.
    $build[$data['link']['mlid']] = $element;
  }
  if ($build) {
    // Make sure drupal_render() does not re-order the links.
    $build['#sorted'] = TRUE;
    // Add the theme wrapper for outer markup.
    // Allow menu-specific theme overrides.
    $build['#theme_wrappers'][] = 'menu_tree__' . strtr($data['link']['menu_name'], '-', '_');
  }

  return $build;
}
/**
 * Helper function to format HTML output for a menu.
 */
function _zentra_menu_links($links, $attributes, $horizontal = FALSE, $depth = 0) {
  dsm('test');
  $output = '';
  if (count($links) > 0) {
    if ($depth == 0) {
      $attributes['class'][] = 'nav';
    }
    $output = '<ul' . drupal_attributes($attributes) . '>';
    $attributes = array();

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out
      // themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }

      $close_tag = FALSE;
      // Seperators
      if (isset($link['href']) && $link['href'] == '<separator>') {
        if ($depth == 0 && $horizontal) {
          $class[] = 'divider-vertical';
        }
        else {
          $class[] = 'divider';
        }
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
        $close_tag = TRUE;
      }
      // Horizontal Dropdowns
      else if ($horizontal && $depth == 0 && isset($link['below']) && !empty($link['below'])) {
        $class[] = 'dropdown';
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
        $link['attributes']['class'][] = 'dropdown-toggle';
        $link['attributes']['data-toggle'] = 'dropdown';
        $link['attributes']['data-target'] = '#';
        $link['html'] = TRUE;
        $link['title'] = $link['title'] . '<b class="caret"></b>';
        if ($link['href'] == '<nolink>') {
          $link['href'] = '';
          $link['external'] = TRUE;
        }
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
        $close_tag = TRUE;
        $attributes['class'][] = 'dropdown-menu';
      }
      // Nav Headers
      else if (isset($link['href']) && $link['href'] == '<nolink>') {
        $class = 'nav-header';
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>' . $link['title'];
        $close_tag = TRUE;
      }
      else {
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
        if (isset($link['href'])) {
          // Pass in $link as $options, they share the same keys.
          $output .= l($link['title'], $link['href'], $link);
        }
        elseif (!empty($link['title'])) {
          // Some links are actually not links, but we wrap these in <span> for
          // adding title and class attributes.
          if (empty($link['html'])) {
            $link['title'] = check_plain($link['title']);
          }
          $span_attributes = '';
          if (isset($link['attributes'])) {
            $span_attributes = drupal_attributes($link['attributes']);
          }
          $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
        }
        $close_tag = TRUE;

      }

      if ($close_tag) {
        // Child links
        if (isset($link['below']) && !empty($link['below'])) {
          $output .= _zentra_menu_links($link['below'], $attributes, $horizontal, $depth + 1);
        }

        $i++;
        $output .= "</li>\n";
      }
    }

    $output .= '</ul>';
  }
  return $output;
}






/**
 * Primary Tabs
 */

/**
 * Implements theme_menu_local_tasks().
 */
function shoelace_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<dl class="tabs">';
    $variables['primary']['#suffix'] = '</dl>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<dl class="tabs pill">';
    $variables['secondary']['#suffix'] = '</dl>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function shoelace_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<dd' . (!empty($variables['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</dd>\n";
}