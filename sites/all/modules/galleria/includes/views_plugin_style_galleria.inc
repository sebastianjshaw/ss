<?php
/**
 * @file
 * Galleria style plugin for the Views module.
 */

/**
  * Implements a style type plugin for the Views module.
  */
class views_plugin_style_galleria extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options += array(
      'galleria_optionset' => array('default' => 'default'),
      'galleria_theme' => array('default' => 'classic'),
    );

    return $options;
  }

  /**
   * Show a form to edit the style options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['galleria'] = array(
      '#type' => 'fieldset',
      '#title' => 'Galleria',
    );

    $optionsets = array();
    foreach (galleria_optionsets() as $name => $optionset) {
      $optionsets[$name] = check_plain($optionset['title']);
    }
    $form['galleria']['galleria_optionset'] = array(
      '#title' => t('Option set'),
      '#type' => 'select',
      '#options' => $optionsets,
      '#default_value' => $this->options['galleria_optionset'],
    );
  }

  /**
   * Performs some cleanup tasks on the options array before saving it.
   */
  function options_submit(&$form, &$form_state) {
    $options = &$form_state['values']['style_options'];

    // Pull the fieldset values one level up
    $options += $options['galleria'];
    unset($options['galleria']);
  }

  /**
   * Searches for the image field to use.
   */
  function find_image_field() {
    foreach ($this->view->display_handler->get_handlers('field') as $id => $handler) {
      if (($handler instanceof views_handler_field_field) && ($handler->field_info['type'] == 'image')) {
        return $id;
        break;
      }
    }
    return FALSE;
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $image_field = $this->find_image_field();
    if ($image_field === FALSE) {
      drupal_set_message(t('Style @style requires an image field to be added.', array('@style' => $this->definition['title'])), 'error');
      return;
    }

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);

    // Render each group separately and concatenate.
    $output = '';
    foreach ($sets as $title => $rows) {
      $output .= theme($this->theme_functions(),
        array(
          'view' => $this->view,
          'options' => $this->options,
          'img_field_name' => $image_field,
          'rows' => $rows,
          'title' => $title)
        );
    }
    return $output;
  }
}
