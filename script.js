function getCart(){
return JSON.parse(localStorage.getItem("cart")) || [];
}

function saveCart(cart){
localStorage.setItem("cart", JSON.stringify(cart));
}

function addToCart(name,price){

let cart = getCart();

let found = cart.find(item => item.name === name);

if(found){
found.quantity++;
}else{
cart.push({name:name,price:price,quantity:1});
}

saveCart(cart);

alert(name+" added to cart");

updateCartCount();

}

function searchProducts(){

let input = document.getElementById("searchInput").value.toLowerCase();

let products = document.getElementsByClassName("product-item");

for(let i=0;i<products.length;i++){

let name = products[i].getElementsByTagName("h3")[0].innerText.toLowerCase();

if(name.includes(input)){
products[i].style.display="block";
}else{
products[i].style.display="none";
}

}

}

function increaseQty(index){

let cart=getCart();

cart[index].quantity++;

saveCart(cart);

displayCart();
updateCartCount();

}

function decreaseQty(index){

let cart=getCart();

if(cart[index].quantity>1){
cart[index].quantity--;
}else{
cart.splice(index,1);
}

saveCart(cart);

displayCart();
updateCartCount();

}

function removeItem(index){

let cart=getCart();

cart.splice(index,1);

saveCart(cart);

displayCart();
updateCartCount();

}

function updateCartCount(){

let cart=getCart();

let count=0;

cart.forEach(item=>{
count+=item.quantity;
});

let el=document.getElementById("cart-count");

if(el) el.innerText=count;

}

function displayCart(){

let cart=getCart();

let items=document.getElementById("cart-items");

if(!items) return;

items.innerHTML="";

let total=0;

cart.forEach((item,index)=>{

items.innerHTML+=`

<div class="card">

<h3>${item.name}</h3>

<p>Price: ₹${item.price}</p>

<div class="qty-box">

<button onclick="decreaseQty(${index})">-</button>

<span>${item.quantity}</span>

<button onclick="increaseQty(${index})">+</button>

</div>

<p>Total: ₹${item.price * item.quantity}</p>

<button onclick="removeItem(${index})">Remove</button>

</div>

`;

total += item.price * item.quantity;

});

let totalBox=document.getElementById("total");

if(totalBox) totalBox.innerText="Total: ₹"+total;

}

function displayOrder(){

let cart=getCart();

let orderItems=document.getElementById("order-items");

let total=0;

cart.forEach(item=>{

orderItems.innerHTML+=`
${item.name} x ${item.quantity} = ₹${item.price * item.quantity}<br>
`;

total+=item.price*item.quantity;

});

document.getElementById("order-total").innerText="Total: ₹"+total;

}
function displayUPIAmount(){
  let cart = getCart();
  let total = 0;

  cart.forEach(item => {
    total += item.price * item.quantity;
  });

  document.getElementById("upi-amount").innerText = "Pay ₹" + total;
}
function togglePayment(){
  let method = document.querySelector('input[name="payment"]:checked').value;

  let upiSection = document.getElementById("upi-section");

  if(method === "UPI"){
    upiSection.style.display = "block";
    displayUPIAmount();
  }else{
    upiSection.style.display = "none";
  }
}

function confirmUPIPayment(){

  let upiId = document.getElementById("upiId").value.trim();

  if(upiId === ""){
    alert("Enter your UPI ID");
    return;
  }

  alert("Payment Successful!");

  placeOrder("UPI", upiId);
}
function handleOrder(){

  let method = document.querySelector('input[name="payment"]:checked').value;

  if(method === "COD"){
    placeOrder("COD", "");
  }else{
    alert("Done");
  }
}

function placeOrder(paymentMethod = "COD", upiId = ""){

let cart = getCart();

if(cart.length === 0){
alert("Cart is empty");
return;
}

let name = document.getElementById("name").value.trim();
let email = document.getElementById("email").value.trim();
let phone = document.getElementById("phone").value.trim();
let address = document.getElementById("address").value.trim();

if(name === "" || email === "" || phone === "" || address === ""){
alert("Please fill all details");
return;
}

let products = "";
let total = 0;

cart.forEach(item=>{
products += item.name + " (" + item.quantity + "), ";
total += item.price * item.quantity;
});

let order = {
  name:name,
  email:email,
  phone:phone,
  address:address,
  products:products,
  total:total,
  paymentMethod: paymentMethod,
  upiId: upiId,
  
};
console.log({
  paymentMethod: paymentMethod,
  upiId: upiId
});
fetch("https://script.google.com/macros/s/AKfycbxSRmJRNPcceVphFIXa84oKRXsTkXjZF_Uz5qROmwJotohA-GQuv98-x3xjDiN4N065/exec", {
  method: "POST",
  mode: "no-cors",
  headers: {
    "Content-Type": "application/json"
  },
  body: JSON.stringify(order)
})
.then(() => {
  alert("Order placed successfully!");

  localStorage.removeItem("cart");

  window.location.href = "index.html";
})
.catch((error) => {
  console.error(error);
  alert("Order failed. Try again.");
});

}




window.onload=function(){

updateCartCount();
displayCart();

}