<?php
function gsapi_admin() {
  $form['gsapi_call'] = array(
    '#title' => 'Type of call',
    '#type' => 'select',
    '#options' => array(
      'getClosestZipCode' => 'getClosestZipCode',
      'getChainsByZip' => 'getChainsByZip',
      'getPromotionsForSearchTerms' => 'getPromotionsForSearchTerms',
      'bar' => 'bar',
    ),
  );

  $form['gsapi_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

function gsapi_admin_submit($form, &$form_state) {
  dpm(gsapi_request($form['gsapi_call']['#value']));
  //dpm($form);
}
