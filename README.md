## Bianca's Flower Shop
## Classes:
* Product: each object of this class represents a flower and contains data about the respective flower (name, product ID, price, number of remaining flower stems)
* Customer: each object of this class represents a customer and contains data about the respective customer (name, surname, email)
* ShoppingCart: the objects of this class contain two dynamically allocated vectors. One stores the prices that the customer must pay based on the selected products and the chosen number of stems for each flower, and another dynamically allocated vector that contains pointers to objects of type Product (to access the names of the chosen products and display them in the interactive menu)
* Adress: the objects of this class contain data about the customer's address (country, city, street, number)
* CreditCard: the objects of this class contain the card information in case the payment is made by card (card number, expiration date, name, CVC)
* Order: the objects of this class provide the necessary information for an order for a specific customer. Thus, it contains variables of types Address, CreditCard and ShoppingCart (which are also objects themselves).
* feedback: the objects of this class each contain a dynamically allocated vector that stores the rating entered from the keyboard for a specific service. Each object of this type corresponds to a specific service (interaction with the florist, variety of products and product prices)

## Project functionalities: (description of the interactive menu and existing methods)
* at the beginning, you see the interactive menu ("show_menu" function)
* the customer can enter the code of a product ("get_code" function), and if the entered code is incorrect, the message "Wrong code! Please enter another one:" is displayed, allowing them to input another code for any product
* when the customer adds a certain number of stems of a particular type to the shopping cart, the "minus_product" function is also called, which decreases that number of stems from the total remaining stems of that product. If the customer wants more stems than the florist has, the product is not added to the shopping cart, and the message "There are not enough stems left! Please come back in the following days." is displayed
* every time something is added to the shopping cart, the customer is asked if they want to choose a code for another product to see its details, and then add it to the cart
* if the user doesn't want to add more products to the shopping cart, they can choose whether to place the order with the previously selected items
* when the order is placed, the total payment is calculated with a discount applied using the static function "sale", and the customer must enter certain information: name, surname, email, card details (optional), country, city, street, number
* in the end, feedback is requested regarding the services provided

#
#### Dogareci Bianca-Alexandra
