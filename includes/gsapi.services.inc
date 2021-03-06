<?php
/**
 * Defines the API services
 */
function gsapi_services_details($requested, $args = null) {
  $url_base = variable_get('gsapi_form_url_base', 'http://uat.groceryserver.com/groceryserver/service');
  $api_version = variable_get('gsapi_form_api_version', 'v10');
  $api_key = variable_get('gsapi_form_api_key', '');
  $client_id = variable_get('gsapi_form_client_id', 'clientId');
  switch ($requested) {
    case 'getClosestZipCode' :
      $url = array(
        $url_base,
        'location',
        'rest',
        $api_version,
        'getClosestZipCode',
        $client_id,
        $api_key,
        'ipAddress',
        gsapi_ip_address(),
      );
      $service = array(
        'method' => 'GET',
        'args' => array(),
        'url' => implode('/', $url),
      );
      break;

    case 'getChainsByZip' :
      $url = array(
        $url_base,
        'grocery',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'getChainsByZipCode',
        'zipCode',
        gsapi_zip(),
      );
      $service = array(
        'method' => 'GET',
        'args' => array(),
        'url' => implode('/', $url),
      );
      break;

    case 'getPromotionsForSearchTerms' :
      $url = array(
        $url_base,
        'searchservice',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'getPromotionsForSearchTerms',
      );
      $service = array(
        'method' => 'POST',
        'args' => array(
          'SearchRequest' => array(
            'zipCode' => gsapi_zip(),
            'maxResult' => 10,
            'ingredientId' => '',
          ),
        ),
        'url' => implode('/', $url),
      );
      foreach ($args as $search_term) {
        $service['args']['SearchRequest']['searchTerms'][] = $search_term;
      }
      break;

    case 'getRecipeDetails' :
      $url = array(
        $url_base,
        'recipe',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'getRecipeDetails',
      );
      $service = array(
        'method' => 'POST',
        'args' => array(
          'GetRecipeDetailsRequest' => array(
            'recipeIdList' => array(),
            'recipeNameList' => array(),
            'zipCode'=> gsapi_zip(),
            'chainIdList' => array(),
          ),
        ),
        'url' => implode('/', $url),
      );
      $service['args']['GetRecipeDetailsRequest']['externalIdList'][] = $args;
      break;

    case 'getPromotionCountForRecipe' :
      $url = array(
        $url_base,
        'grocery',
        'rest',
        $api_version,
        'getPromotionCountForRecipe',
        $client_id,
        $api_key,
      );
      $service = array(
        'method' => 'POST',
        'args' => array(
          'PromotionCountForRecipeRequest' => array(
          ),
        ),
        'url' => implode('/', $url),
      );
      $service['args']['PromotionCountForRecipeRequest']['externalId'] = '1954';//$args[0];
      $service['args']['PromotionCountForRecipeRequest']['sourceId'] = '283034';//$args[0];
      $service['args']['PromotionCountForRecipeRequest']['zipCode'] = gsapi_zip();
      break;

    case 'addItemPromotion' :
      $url = array(
        $url_base,
        'shoppinglist',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'addItemPromotion',
      );
      $service = array(
        'method' => 'POST',
        'args' => array(
          'ItemPromotionRequest' => array(
            'shoppingListId' => '',
            'externalId' => gsapi_uuid(),
            'promotionId' => $args,
            'upcItemId' => '',
            'ingredientId' => '',
            'freeFormIngId' => '',
            'searchTerm' => '',
            'tinyResponse' => 'false',
          ),
        ),
        'url' => implode('/', $url),
      );
      break;

    case 'getShoppingListByExternalId' :
      $url = array(
        $url_base,
        'shoppinglist',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'getShoppingListByExternalId',
        'externalId',
        gsapi_uuid(),
      );
      $service = array(
        'method' => 'GET',
        'args' => array(),
        'url' => implode('/', $url),
      );
      break;

    case 'removePromotionsFromShoppingLists' :
      $url = array(
        $url_base,
        'shoppinglist',
        'rest',
        $api_version,
        $client_id,
        $api_key,
        'removePromotionsFromShoppingLists',
      );
      $service = array(
        'method' => 'POST',
        'args' => array(
          'RemovePromotionsFromShoppingListsRequest' => array(
            'externalIdList' => array(gsapi_uuid()),
            'promotionIdList' => array($args),
          ),
        ),
        'url' => implode('/', $url),
      );
      break;
  }
  return $service;
}
