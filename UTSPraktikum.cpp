#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
using namespace std;

// Struktur untuk menyimpan informasi akun
typedef struct Account {
    int account_number;
    char name[50];
    float balance;
    struct Account *next;
} Account;

void printMenu() {
    cout << "\n===================================" << endl;
    cout << "        BANK LEBIH MANDIRI         " << endl;
    cout << "===================================" << endl;
    cout << setw(3) << "No\t" << "Menu Pilihan" << endl;
    cout << setw(2) << "1\t" << "Pendaftaran Nasabah Bank" << endl;
    cout << setw(2) << "2\t" << "Menampilkan Saldo" << endl;
    cout << setw(2) << "3\t" << "Setor Tunai" << endl;
    cout << setw(2) << "4\t" << "Tarik Tunai" << endl;
    cout << setw(2) << "5\t" << "Transfer Tunai" << endl;
    cout << setw(2) << "0\t" << "Keluar" << endl;
    cout << "===================================" << endl;
}

Account* createAccount(int account_number, char name[], float balance) {
    Account *newAccount = (Account*)malloc(sizeof(Account));
    newAccount->account_number = account_number;
    strcpy(newAccount->name, name);
    newAccount->balance = balance;
    newAccount->next = NULL;
    return newAccount;
}

void addAccount(Account **head, Account *newAccount) {
    if (*head == NULL) {
        *head = newAccount;
        return;
    }
    Account *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newAccount;
}

Account* findAccount(Account *head, int account_number) {
    Account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Fungsi untuk menampilkan saldo rekening
void displayBalance(Account *account) {
    cout << "Saldo pada akun " << account->account_number << ": " << account->balance << endl;
}

// Fungsi untuk menyimpan uang ke dalam rekeing
void deposit(Account *account, float amount) {
    account->balance += amount;
    cout << "Berhasil menyimpan " << amount << " ke rekening " << account->account_number << endl;
}

// Fungsi untuk mengambil uang dari rekening
void withdraw(Account *account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        cout << "Berhasil mengambil " << amount << " dari rekening " << account->account_number << endl;
    } else {
        cout << "Saldo tidak mencukupi untuk melakukan penarikan\n";
    }
}

// Fungsi untuk mentransfer uang dari satu rekening ke rekening lain
void transfer(Account *sender, Account *receiver, float amount) {
    if (sender->balance >= amount) {
        withdraw(sender, amount);
        deposit(receiver, amount);
        cout << "Berhasil mentransfer " << amount << " dari rekening " << sender->account_number << " ke rekening " << receiver->account_number << endl;
    } else {
        cout << "Salo tidak mencukupi untuk melakukan transfer\n";
    }
}

// Fungsi untuk mencetak struk
void printReceipt(Account *account, char transaction[], float amount) {
    cout << "============== STRUK ==============" << endl;
    cout << "Nama Nasabah  : " << account->name << endl;
    cout << "Nomor Rekening: " << account->account_number << endl;
    cout << "Transaksi     : " << transaction << endl;
    cout << "Jumlah        : " << amount << endl;
    cout << "Saldo Akhir   : " << account->balance << endl;
    cout << "===================================" << endl;
}

int main() {
    Account *head = NULL;
    int pin;
    cout << "Masukkan PIN anda: "; cin >> pin;

    if (pin == 1234) {
        cout << "Login berhasil!\n";
        cout << "Anda adalah admin!\n";
        int choice;
        do {
            printMenu();
            cout << "Pilih menu: ";
            cin >> choice;
            system ("cls");

            switch (choice) {
                case 1: {
                    int account_number;
                    char name[50];
                    float balance;
                    cout << "Masukkan nomor rekening: "; cin >> account_number;
                    cout << "Masukkan nama: ";
                    cin.ignore();
                    cin.getline(name, 50);
                    // printf("Masukkan saldo awal: ");
                    // scanf("%f", &balance);
                    cout << "Masukkan saldo awal: "; cin >> balance;
                    Account *newAccount = createAccount(account_number, name, balance);
                    addAccount(&head, newAccount);
                    break;
                }
                case 2: {
                    int account_number;
                    cout << "Masukkan nomor rekening: "; cin >> account_number;
                    Account *account = findAccount(head, account_number);
                    if (account != NULL) {
                        displayBalance(account);
                    } else {
                        cout << "Akun tidak ditemukan\n";
                    }
                    break;
                }
                case 3: {
                    int account_number;
                    float amount;
                    cout << "Masukkan nomor rekening: "; cin >> account_number;
                    Account *account = findAccount(head, account_number);
                    if (account != NULL) {
                        cout << "Masukkan jumlah yang ingin disimpan: "; cin >> amount;
                        deposit(account, amount);
                        printReceipt(account, "Simpan", amount);
                    } else {
                        cout << "Rekening tidak ditemukan\n";
                    }
                    break;
                }
                case 4: {
                    int account_number;
                    float amount;
                    cout << "Masukkan nomor rekening: "; cin >> account_number;
                    Account *account = findAccount(head, account_number);
                    if (account != NULL) {
                        cout << "Masukkan jumlah yang ingin diambil: "; cin >> amount;
                        withdraw(account, amount);
                        printReceipt(account, "Tarik", amount);
                    } else {
                        cout << "Rekening tidak ditemukan\n";
                    }
                    break;
                }
                case 5: {
                    int sender_account, receiver_account;
                    float amount;
                    cout << "Masukkan nomor rekening pengirim: "; cin >> sender_account;
                    cout << "Masukkan nomor rekening penerima: "; cin >> receiver_account;
                    Account *sender = findAccount(head, sender_account);
                    Account *receiver = findAccount(head, receiver_account);
                    if (sender != NULL && receiver != NULL) {
                        cout << "Masukkan jumlah yang ingin ditransfer: "; cin >> amount;
                        transfer(sender, receiver, amount);
                        printReceipt(sender, "Transfer", amount);
                    } else {
                        printf("Salah satu atau kedua akun tidak ditemukan\n");
                        cout << "Salah satu atau kedua rekening tidak ditemukan\n";
                    }
                    break;
                }
                case 0:
                    cout << "Terima kasih telah menggunakan layanan kami.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid\n";
            }
        } while (choice != 0);
    } else {
        cout << "Pin yang anda masukkan salah\n" << endl;
    }
}
