#include <iostream>
#include <locale.h>
#include <string>
#include <bitset>
#include <math.h>
#include<bits/stdc++.h>

using namespace std;

int interface(); //interface do usuário
void ipComClasse(); //calcula IP com classe
void ipCIDR(); //calcula IP sem classe e notação CIDR
void ipDecimal(); //calcula IP sem classe e notação decimal

string add(string a, string b); //soma dois números binários
string decimalParaCIDR (string decimal); //transforma máscara decimal em CIDR

int main()
{
    setlocale(LC_ALL, "portuguese");
    bool continuar = true;

    //o software vai continuar até o usuário não querer mais
    while (continuar == true)
    {
        int escolha = interface();

        switch (escolha)
        {
            case 1:
                ipComClasse();
            break;

            case 2:
                ipCIDR();
            break;

            case 3:
                ipDecimal();
            break;

            default:
                cout << "Opção inválida." << endl;
        }

        cout << "Deseja calcular outro ip? ('sim' para calcular, qualquer outra coisa para sair)" << endl;

        string resposta = "abc";
        cin >> resposta;
        cout << endl;

        if (resposta != "sim")
            continuar = false;
    }


    return 0;

}

int interface()
{
    cout << "Calculadora IPV4" << endl << "Redes de Computadores II" << endl;
    cout << "Aluno: Rafael Oliveira Porfírio" << endl << endl;
    cout << "Opções:" << endl << "1 - Calcular IP com classe" <<endl;
    cout << "2 - Calcular IP sem classe e notação CIDR" <<endl;
    cout << "3 - Calcular IP sem classe e notação decimal" <<endl;
    cout << "Digite o número da opção desejada:" <<endl;

    int choice = 0;
    cin >> choice;
    cout << endl;

    return choice;
}

void ipComClasse()
{
    cout << "Calcular IP com classe" << endl;
    cout << "Digite um IP válido: (padrão: n.n.n.n)" << endl;

    string IP;
    cin >> IP;
    cout << endl;

    bool ipValido = true;
    int pontosCont = 0;

    for(int cont = 0; cont < IP.length(); ++cont)
    {
        //checando se algum caractere que não é número ou ponto está presente
        if(IP[cont]!='1' && IP[cont]!='2' && IP[cont]!='3' && IP[cont]!='4' && IP[cont]!='5' && IP[cont]!='6'
                && IP[cont]!='7' && IP[cont]!='8' && IP[cont]!='9' && IP[cont]!='0' && IP[cont]!='.' )
            ipValido = false;
        //contando os pontos
        else if (IP[cont] == '.')
                ++pontosCont;
    }

    //se há mais/menos octetos do que 4, o IP é inválido
    if (pontosCont != 3)
        ipValido = false;

    //se o IP contiver 4 octetos de apenas pontos e números:
    if (ipValido == true)
    {
        //armazenando os índices dos locais dos pontos do string IP no vetor pontosLocal
        int pontosLocal[3];
        int cont2 = 0;
        for(int cont = 0; cont < IP.length(); ++cont)
        {
            if(IP[cont] == '.')
                {
                    pontosLocal[cont2] = cont;
                    ++cont2;
                }
        }

        //octetos armazenados em strings individuais
        string octeto1, octeto2, octeto3, octeto4;
        octeto1 = IP.substr(0, pontosLocal[0] );
        octeto2 = IP.substr( ( ++pontosLocal[0] ), ( (--pontosLocal[1]) - pontosLocal[0]) );
        octeto3 = IP.substr( ( pontosLocal[1] + 2 ), ( (pontosLocal[2] - 2) - pontosLocal[1]) );
        octeto4 = IP.substr( ( pontosLocal[2] + 1 ), ( IP.length() - (pontosLocal[2] - 2) ) );

        //garantindo valores mínimos e máximos de cada octeto
        if ( stoi(octeto1) > 255 || stoi(octeto1) < 0 )
            ipValido = false;
        else if ( stoi(octeto2) > 255 || stoi(octeto2) < 0 )
            ipValido = false;
        else if ( stoi(octeto3) > 255 || stoi(octeto3) < 0 )
            ipValido = false;
        else if ( stoi(octeto4) > 255 || stoi(octeto4) < 0 )
            ipValido = false;

        char classe;

        //encontrando as classes
        //Class A addresses only include IP starting from 1.x.x.x to 126.x.x.x only. The IP range 127.x.x.x is reserved for loopback IP addresses.
        if ( stoi(octeto1) >= 1 && stoi(octeto1) <= 126 )
            classe = 'A';
        //Class B IP Addresses range from 128.0.x.x to 191.255.x.x.
        else if ( stoi(octeto1) >= 128 && stoi(octeto1) <= 191 && stoi(octeto2) >= 0 && stoi(octeto2) <= 255 )
            classe = 'B';
        //Class C IP addresses range from 192.0.0.x to 223.255.255.x
        else if ( stoi(octeto1) >= 192 && stoi(octeto1) <= 223 && stoi(octeto2) >= 0 && stoi(octeto2) <= 255 && stoi(octeto3) >= 0 && stoi(octeto3) <= 255 )
            classe = 'C';
        //Class D has IP address range from 224.0.0.0 to 239.255.255.255. Class D is reserved for Multicasting.
        else if ( stoi(octeto1) >= 224 && stoi(octeto1) <= 239 && stoi(octeto2) >= 0 && stoi(octeto2) <= 255 && stoi(octeto3) >= 0 && stoi(octeto3) <= 255 && stoi(octeto4) >= 0 && stoi(octeto4) <= 255 )
            classe = 'D';
        //IP addresses in this class ranges from 240.0.0.0 to 255.255.255.254.
        else if ( stoi(octeto1) >= 240 && stoi(octeto1) <= 255 && stoi(octeto2) >= 0 && stoi(octeto2) <= 255 && stoi(octeto3) >= 0 && stoi(octeto3) <= 255 && stoi(octeto4) >= 0 && stoi(octeto4) <= 254 )
            classe = 'E';
        //se não tem classe, IP inválido
        else
            ipValido = false;

        if (ipValido == true)
        {
            if (classe == 'A')
            {
                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Classe:                        \t\t\t" << classe << endl;
                cout << "Mascara decimal:               \t\t\t" << "255.0.0.0" << endl;
                cout << "Mascara CIDR:                  \t\t\t" << "/8" << endl;
                cout << "Número de hosts:               \t\t\t" << "16777214" << endl;
                cout << "Endereço de rede:              \t\t\t" << octeto1 << ".0.0.0" << endl;
                cout << "Endereço de broadcast:         \t\t\t" << octeto1 << ".255.255.255" << endl;
                cout << "Endereço IP inicial utilizável:\t\t\t" << octeto1 << ".0.0.1" << endl;
                cout << "Endereço IP final utilizável:  \t\t\t" << octeto1 << ".255.255.254" << endl << endl;
            }

            else if (classe == 'B')
            {
                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Classe:                        \t\t\t" << classe << endl;
                cout << "Mascara decimal:               \t\t\t" << "255.255.0.0" << endl;
                cout << "Mascara CIDR:                  \t\t\t" << "/16" << endl;
                cout << "Número de hosts:               \t\t\t" << "65534" << endl;
                cout << "Endereço de rede:              \t\t\t" << octeto1 << "." << octeto2 << ".0.0" << endl;
                cout << "Endereço de broadcast:         \t\t\t" << octeto1 << "." << octeto2 << ".255.255" << endl;
                cout << "Endereço IP inicial utilizável:\t\t\t" << octeto1 << "." << octeto2 << ".0.1" << endl;
                cout << "Endereço IP final utilizável:  \t\t\t" << octeto1 << "." << octeto2 << ".255.254" << endl << endl;
            }

            else if (classe == 'C')
            {
                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Classe:                        \t\t\t" << classe << endl;
                cout << "Mascara decimal:               \t\t\t" << "255.255.255.0" << endl;
                cout << "Mascara CIDR:                  \t\t\t" << "/24" << endl;
                cout << "Número de hosts:               \t\t\t" << "254" << endl;
                cout << "Endereço de rede:              \t\t\t" << octeto1 << "." << octeto2 << "." << octeto3 <<  ".0" << endl;
                cout << "Endereço de broadcast:         \t\t\t" << octeto1 << "." << octeto2 << "." << octeto3 << ".255" << endl;
                cout << "Endereço IP inicial utilizável:\t\t\t" << octeto1 << "." << octeto2 << "." << octeto3 <<   ".1" << endl;
                cout << "Endereço IP final utilizável:  \t\t\t" << octeto1 << "." << octeto2 << "." << octeto3 <<   ".254" << endl << endl;
            }

            else if (classe == 'D')
            {
                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Classe:                        \t\t\t" << classe << endl;
                cout << "Endereço reservado para multicast" << endl << endl;
            }

            else if (classe == 'E')
            {
                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Classe:                        \t\t\t" << classe << endl;
                cout << "Endereço reservado para o futuro" << endl << endl;
            }

        }
        else
            cout << "IP inválido." << endl;

    }
    else
        cout << "IP inválido." << endl;

}

void ipCIDR()
{
    cout << "Calcular IP sem classe e notação CIDR" << endl;
    cout << "Digite um IP válido: (padrão: n.n.n.n)" << endl;

    string IP;
    cin >> IP;
    cout << endl;

    bool ipValido = true;
    int pontosCont = 0;

    for(int cont = 0; cont < IP.length(); ++cont)
    {
        //checando se algum caractere que não é número ou ponto está presente
        if(IP[cont]!='1' && IP[cont]!='2' && IP[cont]!='3' && IP[cont]!='4' && IP[cont]!='5' && IP[cont]!='6'
                && IP[cont]!='7' && IP[cont]!='8' && IP[cont]!='9' && IP[cont]!='0' && IP[cont]!='.' )
            ipValido = false;
        //contando os pontos
        else if (IP[cont] == '.')
                ++pontosCont;
    }

    //se há mais/menos octetos do que 4, o IP é inválido
    if (pontosCont != 3)
        ipValido = false;

    //se o IP contiver 4 octetos de apenas pontos e números:
    if (ipValido == true)
    {
        //armazenando os índices dos locais dos pontos do string IP no vetor pontosLocal
        int pontosLocal[3];
        int cont2 = 0;
        for(int cont = 0; cont < IP.length(); ++cont)
        {
            if(IP[cont] == '.')
                {
                    pontosLocal[cont2] = cont;
                    ++cont2;
                }
        }

        //octetos armazenados em strings individuais
        string octeto1, octeto2, octeto3, octeto4;
        octeto1 = IP.substr(0, pontosLocal[0] );
        octeto2 = IP.substr( ( ++pontosLocal[0] ), ( (--pontosLocal[1]) - pontosLocal[0]) );
        octeto3 = IP.substr( ( pontosLocal[1] + 2 ), ( (pontosLocal[2] - 2) - pontosLocal[1]) );
        octeto4 = IP.substr( ( pontosLocal[2] + 1 ), ( IP.length() - (pontosLocal[2] - 2) ) );

        //garantindo valores mínimos e máximos de cada octeto
        if ( stoi(octeto1) > 255 || stoi(octeto1) < 0 )
            ipValido = false;
        else if ( stoi(octeto2) > 255 || stoi(octeto2) < 0 )
            ipValido = false;
        else if ( stoi(octeto3) > 255 || stoi(octeto3) < 0 )
            ipValido = false;
        else if ( stoi(octeto4) > 255 || stoi(octeto4) < 0 )
            ipValido = false;

        if (ipValido == true)
        {
            cout << "Digite a máscara na notação CIDR: (padrão: /n)" << endl;

            string mask;
            cin >> mask;
            cout << endl;

            ipValido = true;

            //garantindo que o primeiro caractere da máscara é '/'
            if ( mask[0]!='/' )
            {
                ipValido = false;
            }

            //garantindo o número de caracteres
            if ( mask.length() < 2 || mask.length() > 3 )
            {
                ipValido = false;
            }
            //garantido que, caso tenha 2 ou 3 caracteres, os caracteres do segundo em diante são numerais
            else
            {
                for ( int cont = 1; cont < mask.length(); ++cont)
                {

                    if ( mask[cont]!='1' && mask[cont]!='2' && mask[cont]!='3' && mask[cont]!='4' && mask[cont]!='5' && mask[cont]!='6'
                        && mask[cont]!='7' && mask[cont]!='8' && mask[cont]!='9' && mask[cont]!='0' )
                        {
                            ipValido = false;
                        }
                }

                //garantindo que, caso tenha 2 ou 3 caracteres, sendo o primeiro / e o resto numerais, o valor numérico seja maior ou igual a 0 e menor ou igual a 32
                if (ipValido == true)
                {
                    if (stoi( mask.substr( 1,( mask.length() - 1 ) ) ) > 32 || stoi( mask.substr( 1,( mask.length() - 1 ) ) ) < 0)
                    {
                        ipValido = false;
                    }
                }

            }

            if (ipValido == true)
            {
                int n = stoi( mask.substr( 1,( mask.length() - 1 ) ) );
                int nClone = n;

                string octetoMascaraB1 = "00000000", octetoMascaraB2 = "00000000",
                    octetoMascaraB3 = "00000000", octetoMascaraB4 = "00000000";

                //criando máscara binária a partir de /n
                for (int cont = 0; cont < 32; ++cont)
                {
                    if(n > 0 && cont >= 0 && cont < 8)
                    {
                        octetoMascaraB1[cont] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 8 && cont < 16)
                    {
                        octetoMascaraB2[cont - 8] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 16 && cont < 24)
                    {
                        octetoMascaraB3[cont - 16] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 24 && cont < 32)
                    {
                        octetoMascaraB4[cont - 24] = '1';
                        --n;
                    }
                }

                //convertendo o IP para binário
                string octeto1B = bitset<8>(stoi(octeto1)).to_string(),
                    octeto2B = bitset<8>(stoi(octeto2)).to_string(),
                    octeto3B = bitset<8>(stoi(octeto3)).to_string(),
                    octeto4B = bitset<8>(stoi(octeto4)).to_string();

                //aplicando a máscara sobre o IP em binário
                string comMascaraB1 = "00000000", comMascaraB2 = "00000000",
                    comMascaraB3 = "00000000", comMascaraB4 = "00000000";

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB1[cont] == '1' && octeto1B[cont] == '1')
                        comMascaraB1[cont] = '1';
                    else
                        comMascaraB1[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB2[cont] == '1' && octeto2B[cont] == '1')
                        comMascaraB2[cont] = '1';
                    else
                        comMascaraB2[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB3[cont] == '1' && octeto3B[cont] == '1')
                        comMascaraB3[cont] = '1';
                    else
                        comMascaraB3[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB4[cont] == '1' && octeto4B[cont] == '1')
                        comMascaraB4[cont] = '1';
                    else
                        comMascaraB4[cont] = '0';
                }

                //transformando o IP com máscara binário em decimal
                string comMascara1 = to_string(stoi(comMascaraB1, nullptr, 2)), comMascara2 = to_string(stoi(comMascaraB2, nullptr, 2)),
                    comMascara3 = to_string(stoi(comMascaraB3, nullptr, 2)), comMascara4 = to_string(stoi(comMascaraB4, nullptr, 2));

                //transformando a máscara binária em decimal
                string mascaraDecimal1 = to_string(stoi(octetoMascaraB1, nullptr, 2)), mascaraDecimal2 = to_string(stoi(octetoMascaraB2, nullptr, 2)),
                    mascaraDecimal3 = to_string(stoi(octetoMascaraB3, nullptr, 2)), mascaraDecimal4 = to_string(stoi(octetoMascaraB4, nullptr, 2));

                //número de hosts
                int hosts = int( pow(2.0, 32 - nClone) ) - 2;

                string notMascaraB1 = "00000000", notMascaraB2 = "00000000",
                    notMascaraB3 = "00000000", notMascaraB4 = "00000000";

                //encontrando not da máscara em binário
                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB1[cont] == '1')
                        notMascaraB1[cont] = '0';
                    else
                        notMascaraB1[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB2[cont] == '1')
                        notMascaraB2[cont] = '0';
                    else
                        notMascaraB2[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB3[cont] == '1')
                        notMascaraB3[cont] = '0';
                    else
                        notMascaraB3[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB4[cont] == '1')
                        notMascaraB4[cont] = '0';
                    else
                        notMascaraB4[cont] = '1';
                }

                //or do IP com o not da máscara para descobrir o último endereço válido
                string ultimoEnderecoB1 = "00000000", ultimoEnderecoB2 = "00000000",
                    ultimoEnderecoB3 = "00000000", ultimoEnderecoB4 = "00000000";

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB1[cont] == '1' || octeto1B[cont] == '1')
                        ultimoEnderecoB1[cont] = '1';
                    else
                        ultimoEnderecoB1[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB2[cont] == '1' || octeto2B[cont] == '1')
                        ultimoEnderecoB2[cont] = '1';
                    else
                        ultimoEnderecoB2[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB3[cont] == '1' || octeto3B[cont] == '1')
                        ultimoEnderecoB3[cont] = '1';
                    else
                        ultimoEnderecoB3[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB4[cont] == '1' || octeto4B[cont] == '1')
                        ultimoEnderecoB4[cont] = '1';
                    else
                        ultimoEnderecoB4[cont] = '0';
                }


                // transformando o último endereço de binário para decimal
                string ultimoEndereco1 = to_string(stoi(ultimoEnderecoB1, nullptr, 2)), ultimoEndereco2 = to_string(stoi(ultimoEnderecoB2, nullptr, 2)),
                    ultimoEndereco3 = to_string(stoi(ultimoEnderecoB3, nullptr, 2)), ultimoEndereco4 = to_string(stoi(ultimoEnderecoB4, nullptr, 2));

                //somando o endereço com máscara com 1 para encontrar primeiro endereço utilizável
                string utilizavelB = add( (comMascaraB1 + comMascaraB2 + comMascaraB3 + comMascaraB4) , "00000000000000000000000000000001");

                //subtraindo o último endereço binário por 1 para encontrar o último endereço utilizável
                string overflow = add( (ultimoEnderecoB1 + ultimoEnderecoB2 + ultimoEnderecoB3 + ultimoEnderecoB4) , "11111111111111111111111111111111");
                int contOverflow = overflow.length() - 32;
                string ultimoUtilizavelB = overflow.substr(contOverflow, 32 );

                string utilizavelB1 = "00000000", utilizavelB2 = "00000000",
                    utilizavelB3 = "00000000", utilizavelB4 = "00000000";

                //transformando primeiro endereço utilizável binário em octetos individuais
                for (int cont = 0; cont < 32; ++cont)
                {
                    if (cont >= 0 && cont < 8)
                    {
                        utilizavelB1[cont] = utilizavelB[cont];
                    }

                    if (cont >= 8 && cont < 16)
                    {
                        utilizavelB2[cont - 8] = utilizavelB[cont];
                    }

                    if (cont >= 16 && cont < 24)
                    {
                        utilizavelB3[cont - 16] = utilizavelB[cont];
                    }

                    if (cont >= 24 && cont < 32)
                    {
                        utilizavelB4[cont - 24] = utilizavelB[cont];
                    }
                }


                string ultimoUtilizavelB1 = "00000000", ultimoUtilizavelB2 = "00000000",
                    ultimoUtilizavelB3 = "00000000", ultimoUtilizavelB4 = "00000000";

                //transformando o último endereço utilizável binário em octetos individuais
                for (int cont = 0; cont < 32; ++cont)
                {
                    if (cont >= 0 && cont < 8)
                    {
                        ultimoUtilizavelB1[cont] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 8 && cont < 16)
                    {
                        ultimoUtilizavelB2[cont - 8] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 16 && cont < 24)
                    {
                        ultimoUtilizavelB3[cont - 16] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 24 && cont < 32)
                    {
                        ultimoUtilizavelB4[cont - 24] = ultimoUtilizavelB[cont];
                    }
                }


                //transformando o primeiro endereço utilizável binário em decimal
                string utilizavelDecimal1 = to_string(stoi(utilizavelB1, nullptr, 2)), utilizavelDecimal2 = to_string(stoi(utilizavelB2, nullptr, 2)),
                    utilizavelDecimal3 = to_string(stoi(utilizavelB3, nullptr, 2)), utilizavelDecimal4 = to_string(stoi(utilizavelB4, nullptr, 2));

                //transformando o último endereço utilizável binário em decimal
                string ultimoUtilizavelDecimal1 = to_string(stoi(ultimoUtilizavelB1, nullptr, 2)), ultimoUtilizavelDecimal2 = to_string(stoi(ultimoUtilizavelB2, nullptr, 2)),
                    ultimoUtilizavelDecimal3 = to_string(stoi(ultimoUtilizavelB3, nullptr, 2)), ultimoUtilizavelDecimal4 = to_string(stoi(ultimoUtilizavelB4, nullptr, 2));


                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Mascara decimal:               \t\t\t" << mascaraDecimal1 << '.' << mascaraDecimal2
                    << '.' << mascaraDecimal3 << '.' << mascaraDecimal4 << endl;
                cout << "Màscara CIDR:                  \t\t\t" << "/" << nClone << endl;
                cout << "Número de hosts:               \t\t\t" << hosts  << endl;
                cout << "Endereço de rede:              \t\t\t" << comMascara1 << '.' << comMascara2
                    << '.' << comMascara3 << '.' << comMascara4 << endl;
                cout << "Endereço de broadcast:         \t\t\t" << ultimoEndereco1 << '.' << ultimoEndereco2
                    << '.' << ultimoEndereco3 << '.' << ultimoEndereco4 << endl;
                cout << "Endereço IP inicial utilizável:\t\t\t" << utilizavelDecimal1 << '.' << utilizavelDecimal2
                    << '.' << utilizavelDecimal3 << '.' << utilizavelDecimal4 << endl;
                cout << "Endereço IP final utilizável:\t\t\t" << ultimoUtilizavelDecimal1 << '.' << ultimoUtilizavelDecimal2
                    << '.' << ultimoUtilizavelDecimal3 << '.' << ultimoUtilizavelDecimal4 << endl << endl;

            }

            else
                cout << "Máscara inválida." << endl;
        }

        else
        cout << "IP inválido." << endl;
    }

    else
        cout << "IP inválido." << endl;
}

void ipDecimal()
{
    cout << "Calcular IP sem classe e notação CIDR" << endl;
    cout << "Digite um IP válido: (padrão: n.n.n.n)" << endl;

    string IP;
    cin >> IP;
    cout << endl;

    bool ipValido = true;
    int pontosCont = 0;

    for(int cont = 0; cont < IP.length(); ++cont)
    {
        //checando se algum caractere que não é número ou ponto está presente
        if(IP[cont]!='1' && IP[cont]!='2' && IP[cont]!='3' && IP[cont]!='4' && IP[cont]!='5' && IP[cont]!='6'
                && IP[cont]!='7' && IP[cont]!='8' && IP[cont]!='9' && IP[cont]!='0' && IP[cont]!='.' )
            ipValido = false;
        //contando os pontos
        else if (IP[cont] == '.')
                ++pontosCont;
    }

    //se há mais/menos octetos do que 4, o IP é inválido
    if (pontosCont != 3)
        ipValido = false;

    //se o IP contiver 4 octetos de apenas pontos e números:
    if (ipValido == true)
    {
        //armazenando os índices dos locais dos pontos do string IP no vetor pontosLocal
        int pontosLocal[3];
        int cont2 = 0;
        for(int cont = 0; cont < IP.length(); ++cont)
        {
            if(IP[cont] == '.')
                {
                    pontosLocal[cont2] = cont;
                    ++cont2;
                }
        }

        //octetos armazenados em strings individuais
        string octeto1, octeto2, octeto3, octeto4;
        octeto1 = IP.substr(0, pontosLocal[0] );
        octeto2 = IP.substr( ( ++pontosLocal[0] ), ( (--pontosLocal[1]) - pontosLocal[0]) );
        octeto3 = IP.substr( ( pontosLocal[1] + 2 ), ( (pontosLocal[2] - 2) - pontosLocal[1]) );
        octeto4 = IP.substr( ( pontosLocal[2] + 1 ), ( IP.length() - (pontosLocal[2] - 2) ) );

        //garantindo valores mínimos e máximos de cada octeto
        if ( stoi(octeto1) > 255 || stoi(octeto1) < 0 )
            ipValido = false;
        else if ( stoi(octeto2) > 255 || stoi(octeto2) < 0 )
            ipValido = false;
        else if ( stoi(octeto3) > 255 || stoi(octeto3) < 0 )
            ipValido = false;
        else if ( stoi(octeto4) > 255 || stoi(octeto4) < 0 )
            ipValido = false;

        if (ipValido == true)
        {
            cout << "Digite a máscara na notação decimal: (padrão: n.n.n.n)" << endl;
            string decimal;
            cin >> decimal;
            string mask = decimalParaCIDR(decimal);
            cout << endl;

            ipValido = true;

            //garantindo que o primeiro caractere da máscara é '/'
            if ( mask[0]!='/' )
            {
                ipValido = false;
            }

            //garantindo o número de caracteres
            if ( mask.length() < 2 || mask.length() > 3 )
            {
                ipValido = false;
            }
            //garantido que, caso tenha 2 ou 3 caracteres, os caracteres do segundo em diante são numerais
            else
            {
                for ( int cont = 1; cont < mask.length(); ++cont)
                {

                    if ( mask[cont]!='1' && mask[cont]!='2' && mask[cont]!='3' && mask[cont]!='4' && mask[cont]!='5' && mask[cont]!='6'
                        && mask[cont]!='7' && mask[cont]!='8' && mask[cont]!='9' && mask[cont]!='0' )
                        {
                            ipValido = false;
                        }
                }

                //garantindo que, caso tenha 2 ou 3 caracteres, sendo o primeiro / e o resto numerais, o valor numérico seja maior ou igual a 0 e menor ou igual a 32
                if (ipValido == true)
                {
                    if (stoi( mask.substr( 1,( mask.length() - 1 ) ) ) > 32 || stoi( mask.substr( 1,( mask.length() - 1 ) ) ) < 0)
                    {
                        ipValido = false;
                    }
                }

            }

            if (ipValido == true)
            {
                int n = stoi( mask.substr( 1,( mask.length() - 1 ) ) );
                int nClone = n;

                string octetoMascaraB1 = "00000000", octetoMascaraB2 = "00000000",
                    octetoMascaraB3 = "00000000", octetoMascaraB4 = "00000000";

                //criando máscara binária a partir de /n
                for (int cont = 0; cont < 32; ++cont)
                {
                    if(n > 0 && cont >= 0 && cont < 8)
                    {
                        octetoMascaraB1[cont] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 8 && cont < 16)
                    {
                        octetoMascaraB2[cont - 8] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 16 && cont < 24)
                    {
                        octetoMascaraB3[cont - 16] = '1';
                        --n;
                    }

                    if(n > 0 && cont >= 24 && cont < 32)
                    {
                        octetoMascaraB4[cont - 24] = '1';
                        --n;
                    }
                }

                //convertendo o IP para binário
                string octeto1B = bitset<8>(stoi(octeto1)).to_string(),
                    octeto2B = bitset<8>(stoi(octeto2)).to_string(),
                    octeto3B = bitset<8>(stoi(octeto3)).to_string(),
                    octeto4B = bitset<8>(stoi(octeto4)).to_string();

                //aplicando a máscara sobre o IP em binário
                string comMascaraB1 = "00000000", comMascaraB2 = "00000000",
                    comMascaraB3 = "00000000", comMascaraB4 = "00000000";

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB1[cont] == '1' && octeto1B[cont] == '1')
                        comMascaraB1[cont] = '1';
                    else
                        comMascaraB1[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB2[cont] == '1' && octeto2B[cont] == '1')
                        comMascaraB2[cont] = '1';
                    else
                        comMascaraB2[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB3[cont] == '1' && octeto3B[cont] == '1')
                        comMascaraB3[cont] = '1';
                    else
                        comMascaraB3[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB4[cont] == '1' && octeto4B[cont] == '1')
                        comMascaraB4[cont] = '1';
                    else
                        comMascaraB4[cont] = '0';
                }

                //transformando o IP com máscara binário em decimal
                string comMascara1 = to_string(stoi(comMascaraB1, nullptr, 2)), comMascara2 = to_string(stoi(comMascaraB2, nullptr, 2)),
                    comMascara3 = to_string(stoi(comMascaraB3, nullptr, 2)), comMascara4 = to_string(stoi(comMascaraB4, nullptr, 2));

                //transformando a máscara binária em decimal
                string mascaraDecimal1 = to_string(stoi(octetoMascaraB1, nullptr, 2)), mascaraDecimal2 = to_string(stoi(octetoMascaraB2, nullptr, 2)),
                    mascaraDecimal3 = to_string(stoi(octetoMascaraB3, nullptr, 2)), mascaraDecimal4 = to_string(stoi(octetoMascaraB4, nullptr, 2));

                //número de hosts
                int hosts = int( pow(2.0, 32 - nClone) ) - 2;

                string notMascaraB1 = "00000000", notMascaraB2 = "00000000",
                    notMascaraB3 = "00000000", notMascaraB4 = "00000000";

                //encontrando not da máscara em binário
                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB1[cont] == '1')
                        notMascaraB1[cont] = '0';
                    else
                        notMascaraB1[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB2[cont] == '1')
                        notMascaraB2[cont] = '0';
                    else
                        notMascaraB2[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB3[cont] == '1')
                        notMascaraB3[cont] = '0';
                    else
                        notMascaraB3[cont] = '1';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (octetoMascaraB4[cont] == '1')
                        notMascaraB4[cont] = '0';
                    else
                        notMascaraB4[cont] = '1';
                }

                //or do IP com o not da máscara para descobrir o último endereço válido
                string ultimoEnderecoB1 = "00000000", ultimoEnderecoB2 = "00000000",
                    ultimoEnderecoB3 = "00000000", ultimoEnderecoB4 = "00000000";

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB1[cont] == '1' || octeto1B[cont] == '1')
                        ultimoEnderecoB1[cont] = '1';
                    else
                        ultimoEnderecoB1[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB2[cont] == '1' || octeto2B[cont] == '1')
                        ultimoEnderecoB2[cont] = '1';
                    else
                        ultimoEnderecoB2[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB3[cont] == '1' || octeto3B[cont] == '1')
                        ultimoEnderecoB3[cont] = '1';
                    else
                        ultimoEnderecoB3[cont] = '0';
                }

                for (int cont = 0; cont < 8; ++cont)
                {
                    if (notMascaraB4[cont] == '1' || octeto4B[cont] == '1')
                        ultimoEnderecoB4[cont] = '1';
                    else
                        ultimoEnderecoB4[cont] = '0';
                }


                // transformando o último endereço de binário para decimal
                string ultimoEndereco1 = to_string(stoi(ultimoEnderecoB1, nullptr, 2)), ultimoEndereco2 = to_string(stoi(ultimoEnderecoB2, nullptr, 2)),
                    ultimoEndereco3 = to_string(stoi(ultimoEnderecoB3, nullptr, 2)), ultimoEndereco4 = to_string(stoi(ultimoEnderecoB4, nullptr, 2));

                //somando o endereço com máscara com 1 para encontrar primeiro endereço utilizável
                string utilizavelB = add( (comMascaraB1 + comMascaraB2 + comMascaraB3 + comMascaraB4) , "00000000000000000000000000000001");

                //subtraindo o último endereço binário por 1 para encontrar o último endereço utilizável
                string overflow = add( (ultimoEnderecoB1 + ultimoEnderecoB2 + ultimoEnderecoB3 + ultimoEnderecoB4) , "11111111111111111111111111111111");
                int contOverflow = overflow.length() - 32;
                string ultimoUtilizavelB = overflow.substr(contOverflow, 32 );

                string utilizavelB1 = "00000000", utilizavelB2 = "00000000",
                    utilizavelB3 = "00000000", utilizavelB4 = "00000000";

                //transformando primeiro endereço utilizável binário em octetos individuais
                for (int cont = 0; cont < 32; ++cont)
                {
                    if (cont >= 0 && cont < 8)
                    {
                        utilizavelB1[cont] = utilizavelB[cont];
                    }

                    if (cont >= 8 && cont < 16)
                    {
                        utilizavelB2[cont - 8] = utilizavelB[cont];
                    }

                    if (cont >= 16 && cont < 24)
                    {
                        utilizavelB3[cont - 16] = utilizavelB[cont];
                    }

                    if (cont >= 24 && cont < 32)
                    {
                        utilizavelB4[cont - 24] = utilizavelB[cont];
                    }
                }


                string ultimoUtilizavelB1 = "00000000", ultimoUtilizavelB2 = "00000000",
                    ultimoUtilizavelB3 = "00000000", ultimoUtilizavelB4 = "00000000";

                //transformando o último endereço utilizável binário em octetos individuais
                for (int cont = 0; cont < 32; ++cont)
                {
                    if (cont >= 0 && cont < 8)
                    {
                        ultimoUtilizavelB1[cont] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 8 && cont < 16)
                    {
                        ultimoUtilizavelB2[cont - 8] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 16 && cont < 24)
                    {
                        ultimoUtilizavelB3[cont - 16] = ultimoUtilizavelB[cont];
                    }

                    if (cont >= 24 && cont < 32)
                    {
                        ultimoUtilizavelB4[cont - 24] = ultimoUtilizavelB[cont];
                    }
                }


                //transformando o primeiro endereço utilizável binário em decimal
                string utilizavelDecimal1 = to_string(stoi(utilizavelB1, nullptr, 2)), utilizavelDecimal2 = to_string(stoi(utilizavelB2, nullptr, 2)),
                    utilizavelDecimal3 = to_string(stoi(utilizavelB3, nullptr, 2)), utilizavelDecimal4 = to_string(stoi(utilizavelB4, nullptr, 2));

                //transformando o último endereço utilizável binário em decimal
                string ultimoUtilizavelDecimal1 = to_string(stoi(ultimoUtilizavelB1, nullptr, 2)), ultimoUtilizavelDecimal2 = to_string(stoi(ultimoUtilizavelB2, nullptr, 2)),
                    ultimoUtilizavelDecimal3 = to_string(stoi(ultimoUtilizavelB3, nullptr, 2)), ultimoUtilizavelDecimal4 = to_string(stoi(ultimoUtilizavelB4, nullptr, 2));


                cout << "Endereço IP:                   \t\t\t" << IP << endl;
                cout << "Mascara decimal:               \t\t\t" << mascaraDecimal1 << '.' << mascaraDecimal2
                    << '.' << mascaraDecimal3 << '.' << mascaraDecimal4 << endl;
                cout << "Màscara CIDR:                  \t\t\t" << "/" << nClone << endl;
                cout << "Número de hosts:               \t\t\t" << hosts  << endl;
                cout << "Endereço de rede:              \t\t\t" << comMascara1 << '.' << comMascara2
                    << '.' << comMascara3 << '.' << comMascara4 << endl;
                cout << "Endereço de broadcast:         \t\t\t" << ultimoEndereco1 << '.' << ultimoEndereco2
                    << '.' << ultimoEndereco3 << '.' << ultimoEndereco4 << endl;
                cout << "Endereço IP inicial utilizável:\t\t\t" << utilizavelDecimal1 << '.' << utilizavelDecimal2
                    << '.' << utilizavelDecimal3 << '.' << utilizavelDecimal4 << endl;
                cout << "Endereço IP final utilizável:\t\t\t" << ultimoUtilizavelDecimal1 << '.' << ultimoUtilizavelDecimal2
                    << '.' << ultimoUtilizavelDecimal3 << '.' << ultimoUtilizavelDecimal4 << endl << endl;

            }

            else
                cout << "Máscara inválida." << endl;
        }

        else
        cout << "IP inválido." << endl;
    }

    else
        cout << "IP inválido." << endl;
}

string decimalParaCIDR (string decimal)
{
    string IP = decimal;

    bool ipValido = true;
    int pontosCont = 0;

    for(int cont = 0; cont < IP.length(); ++cont)
    {
        //checando se algum caractere que não é número ou ponto está presente
        if(IP[cont]!='1' && IP[cont]!='2' && IP[cont]!='3' && IP[cont]!='4' && IP[cont]!='5' && IP[cont]!='6'
                && IP[cont]!='7' && IP[cont]!='8' && IP[cont]!='9' && IP[cont]!='0' && IP[cont]!='.' )
            ipValido = false;
        //contando os pontos
        else if (IP[cont] == '.')
                ++pontosCont;
    }

    //se há mais/menos octetos do que 4, o IP é inválido
    if (pontosCont != 3)
        ipValido = false;

    //se o IP contiver 4 octetos de apenas pontos e números:
    if (ipValido == true)
    {
        //armazenando os índices dos locais dos pontos do string IP no vetor pontosLocal
        int pontosLocal[3];
        int cont2 = 0;
        for(int cont = 0; cont < IP.length(); ++cont)
        {
            if(IP[cont] == '.')
                {
                    pontosLocal[cont2] = cont;
                    ++cont2;
                }
        }

        //octetos armazenados em strings individuais
        string octeto1, octeto2, octeto3, octeto4;
        octeto1 = IP.substr(0, pontosLocal[0] );
        octeto2 = IP.substr( ( ++pontosLocal[0] ), ( (--pontosLocal[1]) - pontosLocal[0]) );
        octeto3 = IP.substr( ( pontosLocal[1] + 2 ), ( (pontosLocal[2] - 2) - pontosLocal[1]) );
        octeto4 = IP.substr( ( pontosLocal[2] + 1 ), ( IP.length() - (pontosLocal[2] - 2) ) );

        //garantindo valores mínimos e máximos de cada octeto
        if ( stoi(octeto1) > 255 || stoi(octeto1) < 0 )
            ipValido = false;
        else if ( stoi(octeto2) > 255 || stoi(octeto2) < 0 )
            ipValido = false;
        else if ( stoi(octeto3) > 255 || stoi(octeto3) < 0 )
            ipValido = false;
        else if ( stoi(octeto4) > 255 || stoi(octeto4) < 0 )
            ipValido = false;

        string octeto1B = bitset<8>(stoi(octeto1)).to_string(),
                    octeto2B = bitset<8>(stoi(octeto2)).to_string(),
                    octeto3B = bitset<8>(stoi(octeto3)).to_string(),
                    octeto4B = bitset<8>(stoi(octeto4)).to_string();

        string totalBinario = octeto1B + octeto2B + octeto3B + octeto4B;
        int contUns = 0;

        for (int cont = 0; cont < totalBinario.length(); ++cont )
        {
            if (totalBinario[cont] == '1')
                ++contUns;
        }

        string n = "/" + to_string(contUns);

        if (ipValido == false)
            return "invalido";
        else
            return n;

        return (octeto1B + '.' + octeto2B + '.' + octeto3B + '.' + octeto4B);
    }
}

string add(string a, string b)
{
   string result = "";
   int temp = 0;
   int size_a = a.size() - 1;
   int size_b = b.size() - 1;
   while (size_a >= 0 || size_b >= 0 || temp == 1){
      temp += ((size_a >= 0)? a[size_a] - '0': 0);
      temp += ((size_b >= 0)? b[size_b] - '0': 0);
      result = char(temp % 2 + '0') + result;
      temp /= 2;
      size_a--; size_b--;
   }
   return result;
}
