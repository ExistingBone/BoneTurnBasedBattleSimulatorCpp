#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int rng_gods;
char wantQuit = 'N';
int action = 0;
string name;
int checked_temp = 0;
int distracted = 0;
bool distracted_bool = false;
bool checked_bool = false;
int turn = 1;
int checked = 0;
int upgrade = 0;

namespace player{
    int HP = 10;
    int MAX_HP = 10;
    int ATK = 2;
    int HEAL = 3;
    string WEAPON;
    int MAX_HEALS = 5;
    int MAX_EMOTES = 3;
    int HEALS = 5;
    int EMOTES = 3;
}

namespace enemy{
    string NAME;
    int HP;
    int MAX_HP;
    int ATK;
    int FIGHT_STYLE;
}

void playerreset() {
    player::HP = player::MAX_HP;
    player::HEALS = player::MAX_HEALS;
    player::EMOTES = player::MAX_EMOTES;
    turn = 1;
    checked = 0;
    upgrade = 0;
}

void attack1() {
    cout << "ENEMY ATTACK:\n";
    if(checked == 1) {
        cout << enemy::NAME << " has attacked you for " << enemy::ATK << " damage\n";
        player::HP = player::HP - enemy::ATK;
        }
    else if(rng_gods == 1 && checked == 1) {
        cout << enemy::NAME << " has failed to attack you\n";
    }
    else if(checked == 0 && rng_gods == 1) {
        cout << "The enemy has failed to attack you\n";
    }
    else {
        if(enemy::HP > 0) {
            cout << "The enemy has attacked you for " << enemy::ATK << " damage\n";
            player::HP = player::HP - enemy::ATK;
        }
        else {
            cout << "The enemy died before being able to attack you\n";
        }
    }
}

void attack2() {
    cout << "ENEMY ATTACK:\n";
    if (rng_gods == 1) {
        cout << "The RNG gods rolled a natural 1 and accidentally killed themselves\n";
        enemy::HP = 0;
    }
    else if (rng_gods >= 5) {
        cout << "The gods of RNG used instakill, which succeeded\n";
        player::HP = 0;
    }
    else {
        cout << "The RNG gods failed to use an instakill attack on you\n";
    }
}

int main()
{
    srand((unsigned) time(NULL));
    cout << "Welcome to the Bone RPG battle simulator!\n";
    cout << "What should your name be?\n";
    cout << "~ ";
    getline(cin, name);

    cout << "What would you like to name your weapon?\n";
    cout << "~ ";
    cin >> player::WEAPON;

    while(wantQuit == 'N' || wantQuit == 'n') {
        playerreset();
        int enemy_choice = 0;
        cout << "Which enemy would you like to battle?\n";
        cout << "1. Stanley | 2. Timothy | 3. Andronxun | 4. Overpowered Demon Lord | 5. RNG Gods\n";
        cout << "~ ";
        cin >> enemy_choice;

        switch(enemy_choice) {
        case 1:
            enemy::NAME = "Stanley";
            enemy::HP = 6;
            enemy::MAX_HP = 6;
            enemy::ATK = 1;
            enemy::FIGHT_STYLE = 1;
            break;
        case 2:
            enemy::NAME = "Timothy";
            enemy::HP = 12;
            enemy::MAX_HP = 12;
            enemy::ATK = 3;
            enemy::FIGHT_STYLE = 1;
            break;
        case 3:
            enemy::NAME = "Andronxun";
            enemy::HP = 18;
            enemy::MAX_HP = 18;
            enemy::ATK = 6;
            enemy::FIGHT_STYLE = 1;
            break;
        case 4:
            enemy::NAME = "Demon Lord";
            enemy::HP = 25;
            enemy::MAX_HP = 25;
            enemy::ATK = 8;
            enemy::FIGHT_STYLE = 1;
            break;
        case 5:
            enemy::NAME = "RNG Gods";
            enemy::HP = 10;
            enemy::MAX_HP = 10;
            enemy::ATK = 9999;
            enemy::FIGHT_STYLE = 2;
            break;
        default:
            cout << "Incorrect option, defaulted to option 1\n\n";
            enemy::NAME = "Stanley";
            enemy::HP = 6;
            enemy::MAX_HP = 6;
            enemy::ATK = 1;
            enemy::FIGHT_STYLE = 1;
            break;
        }


        while(enemy::HP > 0 && player::HP > 0) {
            rng_gods = 1 + (rand() % 10);
            cout << "----------- Turn " << turn << " -----------\n";
            cout << name << ": " << player::HP << "/" << player::MAX_HP << '\n';

            if(checked == 1) {
                cout << '\t' << enemy::NAME << ": " << enemy::HP << "/" << enemy::MAX_HP << '\n';
            }
            else {
                cout << '\t' << "Enemy: " << enemy::HP << '\n';
            }

            cout << "What will you do?\n";
            cout << "1. CHECK | 2. ATTACK | 3. HEAL " << '(' << player::HEALS << '/' << player::MAX_HEALS << ") " << "| 4. FLEE | 5. EMOTE " << '(' << player::EMOTES << '/' << player::MAX_EMOTES << ") " << "| 6. DHIFIJDOI\n";
            cout << "~ ";
            cin >> action;

            switch(action) {
                case 1:
                    cout << "CHECK:\n";
                    cout << "NAME: " << enemy::NAME << '\n';
                    cout << "ATK: " << enemy::ATK << '\n';
                    cout << "HP: " << enemy::MAX_HP << '\n';
                    checked = 1;
                    checked_temp = 1;
                    break;
                case 2:
                    cout << "ATTACK:\n";
                    enemy::HP = enemy::HP - player::ATK;
                    cout << "You attacked " << enemy::NAME << " with your " << player::WEAPON << " dealing " << player::ATK << " DMG" << '\n';
                    break;
                case 3:
                    cout << "HEAL:\n";
                    if(player::HEALS > 0) {
                        cout << "You healed yourself for " << player::HEAL << " HP\n";
                        player::HP = player::HP + player::HEAL;
                        if(player::HP > player::MAX_HP) {
                            player::HP = player::MAX_HP;
                        }
                        player::HEALS = player::HEALS - 1;
                    }
                    else {
                        cout << "You ran out of heals for this battle\n";
                    }
                    break;
                case 4:
                    cout << "You tried to flee, but failed... unsurprisingly\n";
                    cout << "You have successfully wasted your turn, dummy\n";
                    break;
                case 5:
                    if(player::EMOTES > 0) {
                        cout << "You started dancing on the battle field\n";
                        cout << "The enemy got distracted for 2 turns\n";
                        player::EMOTES = player::EMOTES - 1;
                        distracted = 2;
                    }
                    else {
                        cout << "You started dancing on the battle field\n";
                        cout << "The enemy ignored you\n";
                    }
                    break;
                case 6:
                    cout << "You GYGHDKGGJUHUFSYGYUTIO ??? ?????, you were hit with recoilllll\n";
                    player::HP = player::HP - player::ATK;
                    enemy::HP = enemy::HP - (player::ATK * 2);
                    break;
            }

            cout << '\n';
            action = 0;
            turn = turn + 1;

            if(distracted >= 1) {
                distracted = distracted - 1;
                distracted_bool = true;
            }

            if(distracted_bool) {
                cout << "ENEMY ATTACK:\n";
                cout << "The enemy is too distracted to attack you\n";
                distracted_bool = false;
            }
            else if(checked_temp == 1) {
                checked_temp = 0;
            }
            else if(enemy::FIGHT_STYLE == 1) {
                attack1();
            }
            else if(enemy::FIGHT_STYLE == 2) {
                attack2();
            }

        }

        cout << "------- Battle completed -------\n";

        if(enemy::HP <= 0) {
            cout << "What statistic would you like to upgrade by 1?\n";
            cout << "1. Health | 2. Damage | 3. Healing power | 4. Heal amount\n";
            cout << "~ ";
            cin >> upgrade;

            switch(upgrade) {
            case 1:
                cout << "You successfully upgraded your Health!\n\n";
                player::MAX_HP = player::MAX_HP + 1;
                upgrade = 0;
                break;
            case 2:
                cout << "You successfully upgraded your Damage!\n\n";
                player::ATK = player::ATK + 1;
                upgrade = 0;
                break;
            case 3:
                cout << "You successfully upgraded your Healing power!\n\n";
                player::HEAL = player::HEAL + 1;
                upgrade = 0;
                break;
            case 4:
                cout << "You successfully upgraded your amount of Heals!\n\n";
                player::MAX_HEALS = player::MAX_HEALS + 1;
                upgrade = 0;
                break;
            }
        }
        else if(player::HP <= 0) {
            cout << "You lost, and respawned\n\n";
        }

        cout << "Would you like to stop the game? (All your progress will be lost) (Y/N)\n~ ";
        cin >> wantQuit;
        cout << '\n';
    }

    cout << "Thanks for playing!";

    return 0;
}
