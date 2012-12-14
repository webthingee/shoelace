<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 */
?>

  <div id="page">

    <?php if ($main_menu || $secondary_menu): ?>
      <div id="navigation">
          <nav class="top-bar">
            <ul>
              <!-- Title Area -->
              <li class="name">
                <h1>
                  <a href="#">
                    <?php print $site_name; ?>
                  </a>
                </h1>
              </li>
              <li class="toggle-topbar"><a href="#"></a></li>
            </ul>

            <section>
              <ul class="left">
                <?php print render($main_menu_expanded); ?>
              </ul>

              <ul class="right">
                <li class="divider show-for-medium-and-up"></li>
                <li class="has-dropdown">
                <a href="#">User Menu</a>
                <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('dropdown')), 'heading' => NULL)); ?>
              </ul>
            </section>
          </nav>
      </div> <!-- /#navigation -->
    <?php endif; ?>

    <div id="header" class="row"><div class="section clearfix">

      <?php if ($logo): ?>
        <div class="two columns"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a></div>
      <?php endif; ?>

      <?php if ($site_name || $site_slogan): ?>
        <div id="name-and-slogan">
          <?php if ($site_name): ?>
            <?php if ($title): ?>
              <div id="site-name" class="four columns"><strong>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </strong></div>
            <?php else: /* Use h1 when the content title is empty */ ?>
              <h1 id="site-name" class="four columns">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
            <?php endif; ?>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id="site-slogan" class="five columns"><?php print $site_slogan; ?></div>
          <?php endif; ?>
        </div> <!-- /#name-and-slogan -->
      <?php endif; ?>

      <?php print render($page['header']); ?>

    </div></div> <!-- /.section, /#header -->

    <?php if ($breadcrumb): ?>
      <div id="breadcrumb" class="row"><div class="twelve columns"><?php print $breadcrumb; ?></div></div>
    <?php endif; ?>

    <div class="row"><div class="twelve columns">
      <?php print $messages; ?>
    </div></div>

    <div id="main-wrapper" class="row"><div id="main" class="twelve columns clearfix">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
      <?php print render($title_suffix); ?>
      
      <div id="content" class="eight columns column"><div class="section">
        <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
        <a id="main-content"></a>
        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div></div> <!-- /.section, /#content -->

      <?php if ($page['sidebar_first']): ?>
        <div id="sidebar-first" class="column sidebar"><div class="section">
          <?php print render($page['sidebar_first']); ?>
        </div></div> <!-- /.section, /#sidebar-first -->
      <?php endif; ?>

      <?php if ($page['sidebar_second']): ?>
        <div id="sidebar-second" class="column four columns sidebar"><div class="section">
          <?php print render($page['sidebar_second']); ?>
        </div></div> <!-- /.section, /#sidebar-second -->
      <?php endif; ?>

    </div></div> <!-- /#main, /#main-wrapper -->

    <div id="footer"><div class="section">
      <?php print render($page['footer']); ?>
    </div></div> <!-- /.section, /#footer -->

  </div> <!-- /#page -->
