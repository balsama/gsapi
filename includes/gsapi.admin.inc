<?php
function gsapi_admin() {
  $form['gsapi_call'] = array(
    '#title' => 'Type of call',
    '#type' => 'select',
    '#options' => array(
      'foo' => 'foo',
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
  //dpm($form);
}
