<?php
/**
 * Get recipe details
 */
function gsapitest_grd_form() {
  $form['gsapitest_grd_form_heading']['#value'] = '<h2>Get Recipe Details</h2>';

  $form['gsapitest_grd_form_rid'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Recipe ID',
    '#description' => 'Enter the Drupal Node ID of the recipe.',
  );

  $form['gsapitest_grd_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_grd_form_submit($form, &$form_state) {
  dpm(gsapi_grd($form['gsapitest_grd_form_rid']['#value']));
}

/**
 * Get Recipe Promotion Count (Internal API)
 */
function gsapitest_grpc_form() {
  $form['gsapitest_grpc_form_heading']['#value'] = '<h2>Get Recipe Promotion Count</h2>';

  $form['gsapitest_grpc_form_rid'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Recipe ID',
    '#description' => 'Enter the Drupal Node ID of the recipe.',
  );

  $form['gsapitest_grpc_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_grpc_form_submit($form, &$form_state) {
  dpm(gsapi_grpc($form['gsapitest_grpc_form_rid']['#value']));
}

/**
 * Get Promotion Count For Recipe (GS API Function)
 */
function gsapitest_gpcfr_form() {
  $form['gsapitest_gpcfr_form_heading']['#value'] = '<h2>Get Recipe Promotion Count (External)</h2>';

  $form['gsapitest_gpcfr_form_rid'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Recipe ID',
    '#description' => 'Enter the Drupal Node ID of the recipe.',
  );

  $form['gsapitest_gpcfr_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_gpcfr_form_submit($form, &$form_state) {
  dpm(gsapi_request('getPromotionCountForRecipe', $form['gsapitest_gpcfr_form_rid']['#value']));
}

/**
 * Get Item Promotion Count
 */
function gsapitest_gipc_form() {
  $form['gsapitest_gipc_form_heading']['#value'] = '<h2>Get Item Promotion Count</h2>';

  $form['gsapitest_gipc_form_rid'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Recipe ID',
    '#description' => 'Enter the Drupal Node ID of the recipe',
  );

  $form['gsapitest_gipc_form_delta'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Item Delta',
    '#description' => 'Enter the delta (cardinal number) of ingredient.',
  );

  $form['gsapitest_gipc_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_gipc_form_submit($form, &$form_state) {
  dpm(gsapi_gipc($form['gsapitest_gipc_form_rid']['#value'], $form['gsapitest_gipc_form_delta']['#value']));
}

/**
 * Add Item Promotion
 */
function gsapitest_aip_form() {
  $form['gsapitest_aip_form_heading']['#value'] = '<h2>Add Item Promotion</h2>';

  $form['gsapitest_promo_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Promotion ID to add',
    '#required' => TRUE,
    '#description' => 'Promotion IDs are found in the <code>`Get Recipe Details`</code> response in the <code>`specials`</code> array within an ingredient. Note that not all ingredients will have specials.',
  );

  $form['gsapitest_aip_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_aip_form_submit($form, &$form_state) {
  dpm(gsapi_request('addItemPromotion', $form['gsapitest_promo_id']['#value']));
}

/**
 * Remove Item Promotion
 */
function gsapitest_rip_form() {
  $form['gsapitest_rip_form_heading']['#value'] = '<h2>Remove Item Promotion</h2>';

  $form['gsapitest_promo_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Promotion ID to remove',
    '#required' => TRUE,
    '#description' => 'Promotion IDs are found in the <code>`Get Recipe Details`</code> response in the <code>`specials`</code> array within an ingredient. Note that not all ingredients will have specials.',
  );

  $form['gsapitest_rip_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}
function gsapitest_rip_form_submit($form, &$form_state) {
  dpm(gsapi_request('removePromotionsFromShoppingLists', $form['gsapitest_promo_id']['#value']));
}


/**
 * Get Shopping List by ID
 */
function gsapitest_gsl_form() {
  $form['gsapitest_gsl_form_heading']['#value'] = '<h2>Get Shopping List</h2><p>This method does not take any arguments. Returns the shopping list of the current user. You can purge your list by deleting the <code>`gsapi_uuid`</code> cookie.</p><p>If you have not added any items to your Shopping List, this method will create a new empty Shopping List.</p>';

  $form['gsapitest_gsl_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Get shopping list',
  );

  return $form;
}
function gsapitest_gsl_form_submit($form, &$form_state) {
  dpm(gsapi_request('getShoppingListByExternalId'));
}

