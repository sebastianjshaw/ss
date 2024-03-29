<?php
// $Id: sweaver-plugin-config-plugins.tpl.php,v 1.1.4.2 2010/11/05 22:02:02 swentel Exp $

/**
 * @file
 * Template file for the plugins configuration form.
 */

  $count = 0;
?>

<p><?php print t('Enable or disable plugins and select the order of the tabs on the frontend. Some plugins do not provide tabs in the frontend, but only add extra functionality.'); ?></p>

<div id="plugins-configuration-form">

  <table id="plugins-configuration" class="sticky-enabled">
    <thead>
      <tr>
        <th><?php print t('Plugin'); ?></th>
        <th><?php print t('Enabled'); ?></th>
        <th><?php print t('Weight'); ?></th>
      </tr>
    </thead>

    <tbody>
    <?php foreach ($rows as $row): ?>

      <tr class="<?php print $count % 2 == 0 ? 'odd' : 'even'; ?> draggable property-row">
        <td><?php print $row->name; ?></td>
        <td><?php print $row->status; ?></td>
        <td><?php print $row->weight; ?></td>
      </tr>

    <?php endforeach; ?>
    </tbody>
  </table>

  <?php print $submit; ?>

</div>
