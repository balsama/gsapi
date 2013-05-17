gsapi
=====

Drupal wrapper for the Grocery Server API. This implementation requires that
you provide Grocery Server with your recipes and that they have been imported
into the Grocery Service API.

Functions
---------

**Get Recipe Details**

    gsapi_grd($rid)

*Parameters: $rid integer*  
> Recipe ID as defined in the XML document provided to Grocery Server.
> Usually the Drupal Node ID.

*Return: array*  
> Array representing the recipe and any current promotions for ingredients
> based on the user's zip code. Results are cached for 24 hours.

**Get Promotion Count**

    gsapi_gpc($rid)

*Parameters: $rid integer*  
> Recipe ID as defined in the XML document provided to Grocery Server.
> Usually the Drupal Node ID.

*Return: integer*  
> The number of current promotions for the provided Recipe ID.

**Grocery Server Request**

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

**Grocery Server API Zip**

    gsapi_zip()

Wrapper function for GS getClosestZipCode API call. Adds a leading zero if
zip length is 4. Also stores the result in a cookie so we don't need to make
repeated calls to the API.

**Update Zip**

    gsapi_update_zip($zip)

Sets a zip code for the current user.

*Param: $zip integer*  
> five digit integer representing the zip code.


