#include <iostream>
#include <vector>
#include <limits>
#include "npost.h"
// Структура для зберігання користувачів
struct UserInfo {
 std::string email;
 std::string password;
 User userObj;
};
int main() {
 std::cout << " === Курсова робота ===\n"
<< std::endl;
 static Supplier supplier;
 static Manager manager;
 static std::vector<UserInfo> users; // Зберігаємо всіх користувачів
 // Додаємо імітаційний склад з посилками, які можна отримати
 struct WarehouseParcel {
 std::string ttn;
 std::string recipientName;
 std::string recipientPhone;
 std::string address;
 std::string size;
 double weight;
 bool pickedUp = false;
 };
 static std::vector<WarehouseParcel> warehouse = {
 {"TTN12345", "Іван Іванов", "+380991234567", "Київ, вул. Хрещатик 1",
"S", 2.0, false},
 {"TTN54321", "Олена Коваль", "+380501112233", "Київ, вул. Лесі
Українки 10", "L", 5.0, false}
 };
 // Додаємо структуру для імітації посилок постачальника з можливістю
змінювати статус
 struct SupplierParcel {
 std::string ttn;
 std::string recipientName;
 std::string recipientPhone;
 std::string address;
 std::string size;
 double weight;
 std::string status; // "У дорозі", "На складі", "Доставлена"
 };
 static std::vector<SupplierParcel> supplierParcels = {
 {"TTN12345", "Іван Іванов", "+380991234567", "Київ, вул. Хрещатик 1",
"S", 2.0, "У дорозі"},
 {"TTN67890", "Петро Петренко", "+380981112233", "Львів, пл. Ринок 5",
"M", 1.0, "У дорозі"}
 };
 while (true) {
 int role = -1;
 std::cout << "Оберіть роль для входу:\n";
 std::cout << "1. Користувач\n";
 std::cout << "2. Постачальник\n";
 std::cout << "3. Керівник\n";
 std::cout << "Введіть номер ролі: ";
 std::cin >> role;
 std::cin.ignore();
 if (role == 1) {
 while (true) {
 std::cout << "\n=== Меню користувача ===\n";
 std::cout << "1. Зареєструватись\n";
 std::cout << "2. Увійти\n";
 std::cout << "0. Вихід\n";
 std::cout << "Оберіть опцію: ";
 int userOpt;
 std::cin >> userOpt;
 std::cin.ignore();
 if (userOpt == 1) {
 User user;
 user.registerUser();
 // Зберігаємо email і пароль для входу
 UserInfo info;
 std::cout << "Введіть email для збереження: ";
 std::getline(std::cin, info.email);
 std::cout << "Введіть пароль для збереження: ";
 std::getline(std::cin, info.password);
 info.userObj = user;
 users.push_back(info);
 std::cout << "Реєстрація успішна! Тепер увійдіть у систему.\n";
 } else if (userOpt == 2) {
 std::string email, password;
 std::cout << "Введіть email: ";
 std::getline(std::cin, email);
 std::cout << "Введіть пароль: ";
 std::getline(std::cin, password);
 bool found = false;
 for (auto& info : users) {
 if (info.email == email && info.password == password) {
 found = true;
 User& user = info.userObj;
 int choice;
 while (true) {
 std::cout << "\n=== Головне меню ===\n";
 std::cout << "1. Відправлення посилки\n";
 std::cout << "2. Служба підтримки\n";
 std::cout << "3. Відстеження посилки\n";
 std::cout << "4. Додаткові послуги\n";
 std::cout << "5. Налаштування профілю\n";
 std::cout << "6. Мої посилки\n";
 std::cout << "7. Отримати посилку зі складу\n";
 std::cout << "0. Вихід\n";
 std::cout << "Оберіть опцію: ";
 std::cin >> choice;
 std::cin.ignore();
 switch (choice) {
 case 1: {
 // === Покрокове створення посилки ===
 std::string recipientName, recipientAddress, recipientPhone;
 std::cout << "Введіть ім'я отримувача: ";
 std::getline(std::cin, recipientName);
 std::cout << "Введіть телефон отримувача: ";
 std::getline(std::cin, recipientPhone);
 std::string size;
 std::cout << "Виберіть розмір посилки (S/M/L): ";
 std::getline(std::cin, size);
 double weight;
 std::cout << "Введіть вагу посилки (кг): ";
 std::cin >> weight;
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
'\n');
 std::string payment;
 std::cout << "Метод оплати (готівка / карта / післяплата):
";
 std::getline(std::cin, payment);
 PaymentMethod* pm = new PaymentMethod(payment,
"Оплата при оформленні");
 user.linkPaymentMethod(pm);
 std::string deliveryMethod;
 std::cout << "Спосіб доставки (відділення / поштомат /
кур'єр): ";
 std::getline(std::cin, deliveryMethod);
 std::string deliveryAddress;
 std::cout << "Адреса доставки / номер
відділення/поштомату: ";
 std::getline(std::cin, deliveryAddress);
 Recipient recipient(recipientName, deliveryAddress,
recipientPhone);
 Parcel* parcel = new Parcel(&user, recipient);
 parcel->setSize(size);
 parcel->setWeight(weight);
 parcel->setDeliveryMethod(deliveryMethod);
 parcel->setDeliveryAddress(deliveryAddress);
 parcel->setPaymentMethod(pm);
 parcel->generateTTN();
 parcel->calculateCost();
 user.addParcel(parcel);
 break;
 }
 case 2: {
 // --- Меню підтримки ---
 while (true) {
 std::cout << "\n=== Служба підтримки ===\n";
 std::cout << "1. Чат підтримки\n";
 std::cout << "2. Телефон підтримки\n";
 std::cout << "3. FAQ\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть опцію: ";
 int supOpt;
 std::cin >> supOpt;
 std::cin.ignore();
 Support s;
 if (supOpt == 1) {
 s.chatSupport();
 } else if (supOpt == 2) {
 s.phoneSupport();
 } else if (supOpt == 3) {
 // FAQ підменю
 while (true) {
 std::cout << "\n=== FAQ ===\n";
 std::cout << "1. Як відстежити посилку?\n";
 std::cout << "2. Як скасувати доставку?\n";
 std::cout << "3. Як змінити адресу доставки?\n";
 std::cout << "4. Як змінити отримувача?\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть питання: ";
 int faqOpt;
 std::cin >> faqOpt;
 std::cin.ignore();
 if (faqOpt == 1) {
 std::cout << "Щоб відстежити посилку,
скористайтесь функцією 'Відстеження посилки' у головному меню та введіть
TTN.\n";
 } else if (faqOpt == 2) {
 std::cout << "Скасувати доставку можна через
додаткові послуги або звернувшись до служби підтримки.\n";
 } else if (faqOpt == 3) {
 std::cout << "Змінити адресу доставки можна у
розділі 'Додаткові послуги' за TTN вашої посилки.\n";
 } else if (faqOpt == 4) {
 std::cout << "Змінити отримувача можна у розділі
'Додаткові послуги' за TTN вашої посилки.\n";
 } else if (faqOpt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 } else if (supOpt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 break;
 }
 case 3:
 user.trackParcel();
 break;
 case 4: {
 // --- Додаткові послуги ---
 while (true) {
 std::cout << "\n=== Додаткові послуги ===\n";
 std::cout << "1. Змінити адресу доставки\n";
 std::cout << "2. Змінити отримувача посилки\n";
 std::cout << "3. Швидке повернення\n";
 std::cout << "0. Вихід\n";
 std::cout << "Оберіть опцію: ";
 int extraOpt;
 std::cin >> extraOpt;
 std::cin.ignore();
 if (extraOpt == 1) {
 std::cout << "Введіть TTN посилки для зміни адреси:
";
 std::string ttn;
 std::getline(std::cin, ttn);
 Parcel* parcel = user.getParcelByTTN(ttn);
 if (!parcel) {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 continue;
 }
 std::cout << "Введіть новий спосіб доставки
(відділення/поштомат/кур'єр): ";
 std::string newMethod;
 std::getline(std::cin, newMethod);
 std::cout << "Введіть нову адресу доставки/місто: ";
 std::string newAddress;
 std::getline(std::cin, newAddress);
 parcel->setDeliveryMethod(newMethod);
 parcel->setDeliveryAddress(newAddress);
 std::cout << "Адресу доставки змінено!\n";
 } else if (extraOpt == 2) {
 std::cout << "Введіть TTN посилки для зміни
отримувача: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 Parcel* parcel = user.getParcelByTTN(ttn);
 if (!parcel) {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 continue;
 }
 std::cout << "Введіть нове ім'я отримувача: ";
 std::string newName;
 std::getline(std::cin, newName);
 std::cout << "Введіть новий телефон отримувача: ";
 std::string newPhone;
 std::getline(std::cin, newPhone);
 // Оновлення отримувача через зміну адреси
(залишаємо адресу ту ж)
 parcel->setDeliveryAddress(parcel-
>getRecipientAddress());
 Recipient newRecipient(newName, parcel-
>getRecipientAddress(), newPhone);
 // Прямої функції для зміни отримувача немає, але
можна додати метод у Parcel при потребі
 // Тут імітація: просто повідомлення
 std::cout << "Отримувача змінено на: " << newName <<
", " << newPhone << "\n";
 } else if (extraOpt == 3) {
 std::cout << "Введіть TTN посилки для повернення: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 Parcel* parcel = user.getParcelByTTN(ttn);
 if (!parcel) {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 continue;
 }
 parcel->returnToSender();
 } else if (extraOpt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 break;
 }
 case 5:
 user.updateProfile();
 break;
 case 6:
 user.listParcels();
 break;
 case 7: {
 // --- Отримання посилки зі складу ---
 bool anyAvailable = false;
 std::cout << "\nПосилки на складі, які можна
отримати:\n";
 for (const auto& wp : warehouse) {
 if (!wp.pickedUp && (wp.recipientName == user.getName()
|| wp.recipientPhone == user.getPhone())) {
 std::cout << "TTN: " << wp.ttn << ", Адреса: " <<
wp.address << ", Розмір: " << wp.size << ", Вага: " << wp.weight << " кг\n";
 anyAvailable = true;
 }
 }
 if (!anyAvailable) {
 std::cout << "Немає посилок для отримання на ваше ім'я
або телефон.\n";
 break;
 }
 std::cout << "Введіть TTN посилки, яку бажаєте отримати:
";
 std::string ttn;
 std::getline(std::cin, ttn);
 bool foundParcel = false;
 for (auto& wp : warehouse) {
 if (!wp.pickedUp && wp.ttn == ttn && (wp.recipientName
== user.getName() || wp.recipientPhone == user.getPhone())) {
 wp.pickedUp = true;
 std::cout << "Ви успішно отримали посилку TTN: " <<
wp.ttn << "!\n";
 foundParcel = true;
 break;
 }
 }
 if (!foundParcel) {
 std::cout << "Посилка з таким TTN не знайдена або вже
отримана.\n";
 }
 break;
 }
 case 0:
 // Замість return 0; просто break з циклу користувача, щоб
повернутись до вибору ролі
 goto main_menu;
 default:
 std::cout << "Невірна опція. Спробуйте ще раз.\n";
 }
 }
 }
 }
 if (!found) {
 std::cout << "Користувача з такими даними не знайдено!\n";
 }
 } else if (userOpt == 0) {
 goto main_menu;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 } else if (role == 2) {
 while (true) {
 std::cout << "\n=== Меню постачальника ===\n";
 if (!supplier.isRegistered()) {
 std::cout << "1. Зареєструватись\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть опцію: ";
 int opt;
 std::cin >> opt;
 std::cin.ignore();
 if (opt == 1) {
 supplier.registerSupplier();
 } else if (opt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 } else {
 std::cout << "1. Увійти\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть опцію: ";
 int opt;
 std::cin >> opt;
 std::cin.ignore();
 if (opt == 1) {
 if (supplier.login()) {
 // --- Меню постачальника ---
 while (true) {
 std::cout << "\n=== Система постачальника ===\n";
 std::cout << "1. Список посилок для доставки\n";
 std::cout << "2. Переглянути деталі посилки\n";
 std::cout << "3. Змінити статус посилки\n";
 std::cout << "4. Вихід у головне меню\n";
 std::cout << "Оберіть опцію: ";
 int sopt;
 std::cin >> sopt;
 std::cin.ignore();
 if (sopt == 1) {
 std::cout << "Посилки для доставки:\n";
 bool any = false;
 for (const auto& sp : supplierParcels) {
 // Відображаємо всі, але показуємо статус
 std::cout << "TTN: " << sp.ttn << ", Одержувач: " <<
sp.recipientName
 << ", Статус: " << sp.status << "\n";
 any = true;
 }
 if (!any) {
 std::cout << "Немає посилок для доставки.\n";
 }
 } else if (sopt == 2) {
 std::cout << "Введіть TTN посилки: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 bool found = false;
 for (const auto& sp : supplierParcels) {
 if (sp.ttn == ttn) {
 std::cout << "=== Деталі посилки " << sp.ttn << "
===\n";
 std::cout << "Одержувач: " << sp.recipientName <<
"\n";
 std::cout << "Адреса: " << sp.address << "\n";
 std::cout << "Телефон: " << sp.recipientPhone << "\n";
 std::cout << "Вага: " << sp.weight << " кг\n";
 std::cout << "Статус: " << sp.status << "\n";
 found = true;
 break;
 }
 }
 if (!found) {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 }
 } else if (sopt == 3) {
 std::cout << "Введіть TTN посилки для зміни статусу: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 bool found = false;
 for (auto& sp : supplierParcels) {
 if (sp.ttn == ttn) {
 std::cout << "Оберіть новий статус:\n";
 std::cout << "1. Доставлена\n";
 std::cout << "2. У дорозі\n";
 std::cout << "3. На складі\n";
 std::cout << "Оберіть опцію: ";
 int st;
 std::cin >> st;
 std::cin.ignore();
 std::string newStatus;
 if (st == 1) newStatus = "Доставлена";
 else if (st == 2) newStatus = "У дорозі";
 else if (st == 3) newStatus = "На складі";
 else {
 std::cout << "Невірна опція.\n";
 found = true;
 break;
 }
 sp.status = newStatus;
 std::cout << "Статус посилки " << ttn << " змінено на:
" << newStatus << "\n";
 found = true;
 break;
 }
 }
 if (!found) {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 }
 } else if (sopt == 4) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 break;
 }
 } else if (opt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 }
 // Після виходу з меню постачальника повертаємось до вибору ролі
(тобто while(true) main menu)
 continue;
 } else if (role == 3) {
 while (true) {
 std::cout << "\n=== Меню керівника ===\n";
 if (!manager.isRegistered()) {
 std::cout << "1. Зареєструватись\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть опцію: ";
 int opt;
 std::cin >> opt;
 std::cin.ignore();
 if (opt == 1) {
 manager.registerManager();
 } else if (opt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 } else {
 std::cout << "1. Увійти\n";
 std::cout << "0. Назад\n";
 std::cout << "Оберіть опцію: ";
 int opt;
 std::cin >> opt;
 std::cin.ignore();
 if (opt == 1) {
 if (manager.login()) {
 // --- Меню керівника ---
 while (true) {
 std::cout << "\n=== Система керівника ===\n";
 std::cout << "1. Список всіх посилок\n";
 std::cout << "2. Відстеження посилки\n";
 std::cout << "3. Розподіл посилок на складі\n";
 std::cout << "4. Вихід у головне меню\n";
 std::cout << "Оберіть опцію: ";
 int mopt;
 std::cin >> mopt;
 std::cin.ignore();
 if (mopt == 1) {
 // Імітація списку всіх посилок
 std::cout << "Список всіх посилок:\n";
 std::cout << "TTN12345 | Мала | Статус: На складі\n";
 std::cout << "TTN67890 | Середня | Статус: У дорозі\n";
 std::cout << "TTN54321 | Велика | Статус: На складі\n";
 } else if (mopt == 2) {
 std::cout << "Введіть TTN для відстеження: ";
 std::string ttn;
 std::getline(std::cin, ttn);
 // Імітація відстеження
 if (ttn == "TTN12345") {
 std::cout << "TTN12345: На складі, Мала, Одержувач:
Іван Іванов\n";
 } else if (ttn == "TTN67890") {
 std::cout << "TTN67890: У дорозі, Середня, Одержувач:
Петро Петренко\n";
 } else if (ttn == "TTN54321") {
 std::cout << "TTN54321: На складі, Велика, Одержувач:
Олена Коваль\n";
 } else {
 std::cout << "Посилка з таким TTN не знайдена.\n";
 }
 } else if (mopt == 3) {
 std::cout << "=== Розподіл посилок на складі ===\n";
 std::cout << "Малі:\n";
 std::cout << "TTN12345 (Іван Іванов)\n";
 std::cout << "Середні:\n";
 std::cout << "TTN67890 (Петро Петренко)\n";
 std::cout << "Великі:\n";
 std::cout << "TTN54321 (Олена Коваль)\n";
 } else if (mopt == 4) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 break;
 }
 } else if (opt == 0) {
 break;
 } else {
 std::cout << "Невірна опція.\n";
 }
 }
 }
 continue;
 } else {
 std::cout << "Невірна роль. Завершення програми.\n";
 break;
 }
 // Для користувача та керівника після завершення — вихід з програми
 break;
main_menu: ; // label для повернення до головного меню
 }
 return 0;
}
