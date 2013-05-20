<?php
function gsapi_admin() {
  return drupal_get_form('gsapi_form') . drupal_get_form('gsapi_cache_form');
}

function gsapi_form() {
  $form['gsapi_form_url_base'] = array(
    '#type' => 'textfield',
    '#title' => 'URL Base',
    '#default_value' => variable_get('gsapi_form_url_base', 'http://uat.groceryserver.com/groceryserver/service'),
    '#description' => 'Enter the GS API Base URL. The last folder in the URL should be <code>\'service\'</code>. Do not include trailing slash.',
    '#required'=> TRUE,
  );

  $form['gsapi_form_api_key'] = array(
    '#type' => 'textfield',
    '#title' => 'API Key',
    '#default_value' => variable_get('gsapi_form_api_key', ''),
    '#description' => 'Enter your unique API key. Contact your Grocery Server representative if you don\'t know what your API Key is.',
    '#size' => 60,
    '#required' => TRUE,
  );

  $form['gsapi_form_client_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Client ID',
    '#default_value' => variable_get('gsapi_form_client_id', 'clientId'),
    '#description' => 'Enter your Grocery Server Client ID. Just using <code>\'clientId\'</code> seems to work for me.',
    '#size' => 20,
    '#required' => TRUE,
  );

  $form['gsapi_form_api_version'] = array(
    '#type' => 'textfield',
    '#title' => 'API Version',
    '#default_value' => variable_get('gsapi_form_api_version', 'v10'),
    '#description' => 'The API version is defined in part of the request URL. Usually, it is the version number preceeded by the letter <code>\'v\'</code>.',
    '#size' => 3,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function gsapi_cache_form() {
  $form['gsapi_cache_form'] = array(
    '#type' => 'fieldset',
    '#title' => 'Clear Recipe Details Cache',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => '<p>The GS API module automatically caches recipe details by zip code for 24 hours. If bad data is receoived or if GS has recently updated their copy of recipes, it might be useful to purcge these entries. </p><p>Use the button below to delete all locally cached Recipe Details.</p>',
  );

  $form['gsapi_cache_form']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Clear Recipe Detail Cache',
  );

  return $form;
}

function gsapi_cache_form_submit($form, &$form_state) {
  gsapi_clear_rd_cache();
}
