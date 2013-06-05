gsapi - Drupal Grocery Server API
=================================

Drupal wrapper for the Grocery Server API. This implementation requires that
you provide Grocery Server with your recipes and that they have been imported
into the Grocery Service API.

Unless otherwise noted, all services return geo-targeted data automatically
based on the results of the `gsapi_zip()` function. This explains why, for
example, you don't need to provide a zip code argument to geo targeted API
calls.

Functions
---------

###Get Recipe Details###

    gsapi_grd($rid)

*Parameters: $rid integer*  
> Recipe ID as defined in the XML document provided to Grocery Server.
> Usually the Drupal Node ID.

*Return: array*  
> Array representing the recipe and any current promotions for ingredients
> based on the user's zip code. Results are cached for 24 hours.

###Get Recipe Promotion Count###

    gsapi_grpc($rid)

*Parameters: $rid integer*  
> Recipe ID as defined in the XML document provided to Grocery Server.
> Usually the Drupal Node ID.

*Return: integer*  
> The number of current promotions for the provided Recipe ID. Returns
> non-boolean `0` for no results.

###Get Item Promotion Count###

    gsapi_gipc($rid, $delta)

*Parameter: $rid integer*
> Recipe ID as defined in the XML document provided to Grocery Server.
> Usually the Drupal Node ID.

*Parameter: $delta integer*
> Line Item of ingredient (first ingredient = `0`)

*Return: integer*
> The number of current promotions for the item. Returns non-boolean `0` for no
> results.

###Grocery Server Request###

    gsapi_request($service, $args = null)

Interacts directly with the Grocery Server API.

*Parameter: $service string*  
  Allowed Values (See `gsapi.services.inc`:

* `getClosestZipCode`
  > Returns the closest zip code based on IP address. User wrapper function
  > `gsapi_zip` instead which caches the results and will return user overriden
  > values and also fixes an issue with leading zeros.

* `getChainsByZip`
  > Returns a list of grocery chains in the user's area based on zip code.

* `getPromotionsForSearchTerms`
  > Returns a list of promotions related to the search terms in the user's area
  > based on zip code.

  This value requires a second argument `$args` string:
  > String representing the terms to search.

* `getRecipeDetails`
  > Returns details of a recipe. Use the wrapper function `gsapi_grd()` which
  > caches the results of this method instead.

  This value requires a second argument `$args` integer:
  > Recipe ID

* `addItemPromotion`
  > Adds a promotion to the current user's Shopping List.

  This value requires a second argument `$args` integer:
  > Promotion ID as defined internally by Grocery Server.

* `removePromotionsFromShoppingLists`
  > Same as `addItemPromotion` except removes the provided Promotion rather
  > than adding.

* `getShoppingListByExternalId`
  > Returns the Shopping List for the current user.

  This value requires a second argument `$args` string
  > GS Universally Unique Identifier. 16 character string identifying the
  > current anonymous user to the GS API. This value can be found in the
  `$_COOKIE['gsapi_uuid']`.

###Grocery Server API Zip###

    gsapi_zip()

Wrapper function for GS getClosestZipCode API call. Adds a leading zero if
zip length is 4. Also stores the result in a cookie so we don't need to make
repeated calls to the API.

###Update Zip###

    gsapi_update_zip($zip)

Sets a zip code for the current user.

*Param: $zip integer*  
> five digit integer representing the zip code.

Javascript Wrapper
------------------

The GS API JS module provides javascript wrappers to most of these functions.
The wrappers fall into two categories:

1. Local page that delivers json.
2. Wrapper functions for adding and removing items from a user's Shopping List
   and various ingredient/promotion functions.
3. As additions to the `Drupal.settings` object.

###Local page that delivers json###

    /gsapijs/request/[service]/[rid]||[pid]||[[rid]|[delta]]

*Argument 2: service; allowed values:*

* `grd` (Get Recipe Details)
  > Requires `rid` (Recipe ID) as `arg(3)`. Drupal Node ID of recipe.  
  > **Note**: this object is already available as part of the
  > `Drupal.settings` array on recipe pages. See below.

* `grpc` (Get Recipe Promotion Count).
  > Requires `rid` (Recipe ID) as `arg(3)`. Drupal Node ID of recipe.

* `gipc` (Get Item Promotion Count)
  > Requires a combination of `rid` (Recipe ID) and `delta` seperated by a
  > pipe as arg(3). E.g.: `[[rid]|[delta]]

* `aip` (Add Item Promotion)
  > Requires `pid` (Promotion ID) as `arg(3).` GS internal ID of a promotion.  
  > **Note:** this functionality has a JS wrapper function
  > `gsapijs_sl_promotion(op, pid)` provided. See below.

* `rip` (Remove Item Promotion)  
  > Requires `pid` (Promotion ID) as `arg(3).` GS internal ID of a promotion.
  > **Note:** this functionality has a JS wrapper function
  > `gsapijs_sl_promotion(op, pid)` provided. See below.

* `gsl` (Get Shopping List)  
  > Does not use `arg(3)` but due to Drupal's menu system, you will need to
  > pass something as a placeholder.

###Wrapper function for adding and removing Promotions from Shopping Lists and various other functions.###

    gsapijs(op, pid)

*Param string op*
> Either `aip` or `rip` (Add/Remove Item Promotion respectively).

*Param int Promotion ID*
> The promotion ID returned from the Get Recipe Details call.

**Get Item Promotion Count - Local**

    gsapijs_gipc_local(delta)

> This function should be used in place of the identical
> `gsapijs('gipc', delta)` function when being called from a recipe node. It
> uses the preloaded information from the `Drupal.settings` object and is
> therefore muchmore effecient.


###Additions to the Drupal.settings array###

    Drupal.settings.gsapijs.recipe_details

The entire result of the Get Recipe Details call is available on recipe node
pages via the above.

##A note about Shopping Lists##
Shopping lists are created per user as defined by the `gsapi_uuid` cookie. When
needed, the `gsapi_uuid` is created and stored as a session cookie. Future
calls to the API pertaining to shopping lists will use that UUID to udentify
the ShoppingLlist that should be added to, removed from, or returned.

As noted above, the shopping list cookie and perforce the Shopping List is not
persistent throughout sessions. That is, if a user closes their browser, they
will loose theie shopping list.
