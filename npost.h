#ifndef Npost_H
#define Npost_H
#include <map>
#include <string>
#include <vector>
// Попереднє оголошення для уникнення циклічної залежності
class Parcel;
// Клас Платіжний метод
class PaymentMethod {
private:
 std::string type;
 std::string details;
public:
 PaymentMethod(const std::string& type = "", const std::string& details = "");
 void charge();
};
// Клас Отримувач
class Recipient {
private:
 std::string name;
 std::string address;
 std::string phone;
public:
 Recipient(const std::string& name, const std::string& address, const std::string&
phone);
 void confirmReceipt();
 void refuseParcel();
 std::string getName() const;
 std::string getPhone() const;
 std::string getAddress() const;
};
// Клас Страхування
class Insurance {
private:
 double amount;
 bool isActive;
public:
 Insurance(double amount = 0.0);
 void activate();
 void claim();
};
// Клас Сповіщення
class NotificationService {
public:
 void sendSMS(const std::string& message, const std::string& phone);
 void sendEmail(const std::string& message, const std::string& email);
};
// Клас Підтримка
class Support {
public:
 void chatSupport();
 void phoneSupport();
 void getFAQ();
};
// Клас Користувач
class User {
private:
 int id;
 std::string name;
 std::string email;
 std::string phone;
 std::string password;
 PaymentMethod* paymentMethod;
 std::map<std::string, Parcel*> parcels;
public:
 User();
 void registerUser();
 void verifyAccount();
 void linkPaymentMethod(PaymentMethod* method);
 void trackParcel();
 void requestSupport();
 void updateProfile();
 void addParcel(Parcel* parcel);
 void listParcels();
 Parcel* getParcelByTTN(const std::string& ttn);
 void sendParcel();
 // --- Додаємо геттери для імені та телефону ---
 std::string getName() const { return name; }
 std::string getPhone() const { return phone; }
};
// Клас Посилка
class Parcel {
private:
 std::string ttn;
 User* sender;
 Recipient recipient;
 std::string packageType;
 std::string deliveryMethod;
 PaymentMethod* paymentMethod;
 std::string status;
 std::string promoCode;
 Insurance* insurance;
 std::string size;
 double weight;
public:
 Parcel(User* sender, const Recipient& recipient);
 double calculateCost();
 void generateTTN();
 void cancelDelivery();
 void returnToSender();
 void applyHoldService();
 std::string getTTN() const;
 void setSize(const std::string& s);
 void setWeight(double w);
 void setDeliveryMethod(const std::string& method);
 void setDeliveryAddress(const std::string& addr);
 void setPaymentMethod(PaymentMethod* pm);
 std::string getRecipientName() const;
 std::string getRecipientAddress() const;
 std::string getRecipientPhone() const;
 std::string getStatus() const;
 std::string getSize() const;
 double getWeight() const;
 std::string getDeliveryMethod() const;
};
// Клас Доставка
class Delivery {
private:
 std::string route;
 std::string status;
 std::string currentLocation;
public:
 void updateStatus(const std::string& newStatus);
 void changeRecipient(const Recipient& newRecipient);
 void redirectDelivery(const std::string& newAddress);
};
// Клас Постачальник
class Supplier : public User {
private:
 int id;
 std::string name;
 std::string email;
 std::string phone;
 std::string password;
 bool registered;
public:
 Supplier();
 void registerSupplier();
 void verifyAccount();
 bool isRegistered() const;
 bool login();
};
// Клас Керівник
class Manager : public User {
private:
 int id;
 std::string name;
 std::string email;
 std::string phone;
 std::string password;
 bool registered;
public:
 Manager();
 void registerManager();
 void verifyAccount();
 bool isRegistered() const;
 bool login();
};
#endif // NPOST_H