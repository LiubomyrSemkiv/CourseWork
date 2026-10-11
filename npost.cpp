#include "npost.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
// === PaymentMethod ===
PaymentMethod::PaymentMethod(const std::string& type, const std::string&
details)
 : type(type), details(details) {
}
void PaymentMethod::charge() {
 std::cout << "Charging using " << type << ": " << details << std::endl;
}
// === Recipient ===
Recipient::Recipient(const std::string& name, const std::string& address, const
std::string& phone)
 : name(name), address(address), phone(phone) {
}
std::string Recipient::getName() const {
 return name;
}
std::string Recipient::getPhone() const {
 return phone;
}
void Recipient::confirmReceipt() {
 std::cout << "Recipient " << name << " confirmed receipt.\n";
}
void Recipient::refuseParcel() {
 std::cout << "Recipient " << name << " refused the parcel.\n";
}
std::string Recipient::getAddress() const {
 return address;
}
// === Insurance ===
Insurance::Insurance(double amount)
 : amount(amount), isActive(false) {
}
void Insurance::activate() {
 isActive = true;
 std::cout << "Insurance activated for amount: " << amount << "\n";
}
void Insurance::claim() {
 if (isActive)
 std::cout << "Claim processed for insurance amount: " << amount << "\n";
 else
 std::cout << "Insurance is not active!\n";
}
// === NotificationService ===
void NotificationService::sendSMS(const std::string& message, const std::string&
phone) {
 std::cout << "Sending SMS to " << phone << ": " << message << std::endl;
}
void NotificationService::sendEmail(const std::string& message, const std::string&
email) {
 std::cout << "Sending Email to " << email << ": " << message << std::endl;
}
// === Support ===
void Support::chatSupport() {
 std::cout << "Введіть ваше запитання: ";
 std::string question;
 std::getline(std::cin, question);
 std::cout << "Ваш запит буде розглянуто відповідальними працівниками
компанії.\n";
}
void Support::phoneSupport() {
 std::cout << "Phone support is available at 0-800-XXX-XXX.\n";
}
void Support::getFAQ() {
 std::cout << "Frequently Asked Questions: \n1. How to track a parcel?\n2. How
to cancel delivery?\n";
}
// === User ===
User::User() : id(0), paymentMethod(nullptr) {}
void User::registerUser() {
 std::cout << "Registering user...\n";
 std::cout << "Enter name: ";
 std::getline(std::cin, name);
 std::cout << "Enter email: ";
 std::getline(std::cin, email);
 std::cout << "Enter phone: ";
 std::getline(std::cin, phone);
 std::cout << "Enter password: ";
 std::getline(std::cin, password);
 std::srand(static_cast<unsigned int>(std::time(0)));
 id = rand() % 10000;
 std::cout << "Verification code sent to " << email << " or " << phone << "\n";
 std::string code;
 std::cout << "Enter verification code: ";
 std::getline(std::cin, code);
 verifyAccount();
}
void User::verifyAccount() {
 std::cout << "Account verified successfully!\n";
}
void User::linkPaymentMethod(PaymentMethod* method) {
 paymentMethod = method;
}
void User::trackParcel() {
 std::cout << "Введіть TTN для відстеження: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 // Імітація статусу
 if (ttn == "TTN12345") {
 std::cout << "TTN12345: На складі, Мала, Одержувач: Іван Іванов\n";
 } else if (ttn == "TTN67890") {
 std::cout << "TTN67890: У дорозі, Середня, Одержувач: Петро
Петренко\n";
 } else if (ttn == "TTN54321") {
 std::cout << "TTN54321: На складі, Велика, Одержувач: Олена Коваль\n";
 } else {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 }
}
void User::requestSupport() {
 Support s;
 s.chatSupport();
}
void User::updateProfile() {
 std::cout << "=== Налаштування профілю ===\n";
 std::cout << "1. Змінити email\n2. Змінити телефон\n3. Змінити
пароль\nОберіть опцію: ";
 int opt;
 std::cin >> opt;
 std::cin.ignore();
 switch (opt) {
 case 1:
 std::cout << "Новий email: ";
 std::getline(std::cin, email);
 break;
 case 2:
 std::cout << "Новий телефон: ";
 std::getline(std::cin, phone);
 break;
 case 3:
 std::cout << "Новий пароль: ";
 std::getline(std::cin, password);
 break;
 default:
 std::cout << "Невірна опція.\n";
 }
}
void User::addParcel(Parcel* parcel) {
 parcels[parcel->getTTN()] = parcel;
}
void User::listParcels() {
 if (parcels.empty()) {
 std::cout << "У вас немає посилок." << std::endl;
 return;
 }
 std::cout << "Список ваших посилок:" << std::endl;
 for (const auto& [ttn, parcel] : parcels) {
 std::cout << "TTN: " << ttn << ", Статус: " << parcel->getStatus() <<
std::endl;
 }
 std::cout << "Введіть TTN для перегляду деталей або 0 для виходу: ";
 std::string selectedTTN;
 std::cin >> selectedTTN;
 if (selectedTTN == "0") return;
 Parcel* parcel = getParcelByTTN(selectedTTN);
 if (!parcel) {
 std::cout << "Посилка з таким TTN не знайдена." << std::endl;
 return;
 }
 std::cout << "=== Деталі посилки ===" << std::endl;
 std::cout << "TTN: " << parcel->getTTN() << std::endl;
 std::cout << "Ім'я отримувача: " << parcel->getRecipientName() << std::endl;
 std::cout << "Адреса доставки: " << parcel->getRecipientAddress() <<
std::endl;
 std::cout << "Телефон отримувача: " << parcel->getRecipientPhone() <<
std::endl;
 std::cout << "Тип пакування: " << parcel->getSize() << std::endl;
 std::cout << "Вага: " << parcel->getWeight() << " кг" << std::endl;
 std::cout << "Спосіб доставки: " << parcel->getDeliveryMethod() << std::endl;
 std::cout << "Статус: " << parcel->getStatus() << std::endl;
}
Parcel* User::getParcelByTTN(const std::string& ttn) {
 if (parcels.count(ttn)) return parcels[ttn];
 return nullptr;
}
void User::sendParcel() {
 std::string recipientName, recipientAddress, recipientPhone;
 std::cout << "\n=== Відправка посилки ===\n";
 std::cout << "Ім’я отримувача: ";
 std::getline(std::cin, recipientName);
 std::cout << "Телефон отримувача: ";
 std::getline(std::cin, recipientPhone);
 Recipient r(recipientName, "", recipientPhone);
 Parcel* parcel = new Parcel(this, r);
 std::string size;
 double weight;
 std::cout << "Розмір посилки (S/M/L): ";
 std::getline(std::cin, size);
 std::cout << "Вага (кг): ";
 std::cin >> weight;
 std::cin.ignore();
 parcel->setSize(size);
 parcel->setWeight(weight);
 std::string method;
 std::cout << "Метод доставки (відділення / поштомат / кур’єр): ";
 std::getline(std::cin, method);
 parcel->setDeliveryMethod(method);
 std::string address;
 std::cout << "Адреса доставки: ";
 std::getline(std::cin, address);
 parcel->setDeliveryAddress(address);
 parcel->setPaymentMethod(paymentMethod);
 parcel->generateTTN();
 parcel->calculateCost();
 addParcel(parcel);
 std::cout << "Статус: У дорозі\n";
}
// === Parcel ===
Parcel::Parcel(User* sender, const Recipient& recipient)
 : sender(sender), recipient(recipient), paymentMethod(nullptr),
insurance(nullptr) {
 status = "Created";
}
double Parcel::calculateCost() {
 double cost = 100.0; // базова вартість
 if (promoCode == "DISCOUNT10") {
 cost *= 0.9;
 }
 std::cout << "Total cost: " << cost << std::endl;
 return cost;
}
void Parcel::generateTTN() {
 std::srand(static_cast<unsigned int>(std::time(0)));
 ttn = "TTN" + std::to_string(rand() % 100000);
 std::cout << "Generated TTN: " << ttn << std::endl;
}
void Parcel::cancelDelivery() {
 status = "Canceled";
 std::cout << "Parcel delivery canceled.\n";
}
void Parcel::returnToSender() {
 status = "Returned";
 std::cout << "Parcel is returning to sender.\n";
}
void Parcel::applyHoldService() {
 std::cout << "Hold service activated. Parcel will be held at the branch.\n";
}
std::string Parcel::getTTN() const {
 return ttn;
}
void Parcel::setSize(const std::string& s) {
 size = s;
}
void Parcel::setWeight(double w) {
 weight = w;
}
void Parcel::setDeliveryMethod(const std::string& method) {
 deliveryMethod = method;
}
void Parcel::setDeliveryAddress(const std::string& addr) {
 recipient = Recipient(recipient.getName(), addr, recipient.getPhone());
}
void Parcel::setPaymentMethod(PaymentMethod* pm) {
 paymentMethod = pm;
}
std::string Parcel::getRecipientName() const {
 return recipient.getName();
}
std::string Parcel::getRecipientAddress() const {
 return recipient.getAddress(); // Потрібен метод getAddress() у Recipient
}
std::string Parcel::getRecipientPhone() const {
 return recipient.getPhone(); // Потрібен метод getPhone() у Recipient
}
std::string Parcel::getStatus() const {
 return status;
}
std::string Parcel::getSize() const {
 return size;
}
double Parcel::getWeight() const {
 return weight;
}
std::string Parcel::getDeliveryMethod() const {
 return deliveryMethod;
}
// === Delivery ===
void Delivery::updateStatus(const std::string& newStatus) {
 status = newStatus;
 std::cout << "Status updated to: " << status << std::endl;
}
void Delivery::changeRecipient(const Recipient& newRecipient) {
 std::cout << "Recipient has been changed to: " << newRecipient.getName() <<
std::endl;
}
void Delivery::redirectDelivery(const std::string& newAddress) {
 route = newAddress;
 std::cout << "Delivery address changed to: " << newAddress << std::endl;
}
// === Supplier ===
Supplier::Supplier() : id(0), registered(false) {}
void Supplier::registerSupplier() {
 if (registered) {
 std::cout << "Постачальник вже зареєстрований.\n";
 return;
 }
 std::cout << "Реєстрація постачальника...\n";
 std::cout << "Введіть ім'я: ";
 std::getline(std::cin, name);
 std::cout << "Введіть email: ";
 std::getline(std::cin, email);
 std::cout << "Введіть телефон: ";
 std::getline(std::cin, phone);
 std::cout << "Введіть пароль: ";
 std::getline(std::cin, password);
 std::srand(static_cast<unsigned int>(std::time(0)));
 id = rand() % 10000;
 std::cout << "Код підтвердження надіслано на " << email << " або " << phone
<< "\n";
 std::string code;
 std::cout << "Введіть код підтвердження: ";
 std::getline(std::cin, code);
 verifyAccount();
 registered = true;
 std::cout << "Реєстрація постачальника завершена!\n";
}
void Supplier::verifyAccount() {
 std::cout << "Обліковий запис постачальника підтверджено!\n";
}
bool Supplier::isRegistered() const {
 return registered;
}
bool Supplier::login() {
 if (!registered) {
 std::cout << "Постачальник ще не зареєстрований!\n";
 return false;
 }
 std::string inputEmail, inputPassword;
 std::cout << "Введіть email: ";
 std::getline(std::cin, inputEmail);
 std::cout << "Введіть пароль: ";
 std::getline(std::cin, inputPassword);
 if (inputEmail == email && inputPassword == password) {
 std::cout << "Вхід виконано успішно!\n";
 return true;
 } else {
 std::cout << "Невірний email або пароль!\n";
 return false;
 }
}
// === Manager ===
Manager::Manager() : id(0), registered(false) {}
void Manager::registerManager() {
 if (registered) {
 std::cout << "Керівник вже зареєстрований.\n";
 return;
 }
 std::cout << "Реєстрація керівника...\n";
 std::cout << "Введіть ім'я: ";
 std::getline(std::cin, name);
 std::cout << "Введіть email: ";
 std::getline(std::cin, email);
 std::cout << "Введіть телефон: ";
 std::getline(std::cin, phone);
 std::cout << "Введіть пароль: ";
 std::getline(std::cin, password);
 std::srand(static_cast<unsigned int>(std::time(0)));
 id = rand() % 10000;
 std::cout << "Код підтвердження надіслано на " << email << " або " << phone
<< "\n";
 std::string code;
 std::cout << "Введіть код підтвердження: ";
 std::getline(std::cin, code);
 verifyAccount();
 registered = true;
 std::cout << "Реєстрація керівника завершена!\n";
}
void Manager::verifyAccount() {
 std::cout << "Обліковий запис керівника підтверджено!\n";
}
bool Manager::isRegistered() const {
 return registered;
}
bool Manager::login() {
 if (!registered) {
 std::cout << "Керівник ще не зареєстрований!\n";
 return false;
 }
 std::string inputEmail, inputPassword;
 std::cout << "Введіть email: ";
 std::getline(std::cin, inputEmail);
 std::cout << "Введіть пароль: ";
 std::getline(std::cin, inputPassword);
 if (inputEmail == email && inputPassword == password) {
 std::cout << "Вхід виконано успішно!\n";
 return true;
 } else {
 std::cout << "Невірний email або пароль!\n";
 return false;
 }
}
