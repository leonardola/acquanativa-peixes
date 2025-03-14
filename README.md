# acquanativa-peixes
Código para controle de oxigênio dissolvido usando o shield da [acquanativa](https://www.acquanativa.com.br/) para Arduino

Este projeto controla 1 relé que pode ser utilizado para controlar aeradores

## Como instalar?

- Baixe este projeto
- Abra o arquivo `UNOShield_OD/UNOShield_OD.ino` na IDE Arduino
- Não coloque ainda a shield. Caso contrário você receberá um erro ao tentar upar o firmware
- Compile tudo e envie para o Arduino
- Coloque a shield no arduino.
- Siga os passos no cabeçalho do arquivo `.ino` para calibração
- Conecte um relé ao pino 13 do shield/Arduino


## Quais valores de oxigênio dissolvidos estão configurados?

Por padrão sempre que o oxigênio dissolvido estiver abaixo de 5 mg/l o aerador será ligado. Sempre que estiver acima de 6 mg/l o aerador será desligado.

## Como mudar os parâmetros para controlar o aerador?

- Edite o arquivo `UNOShield_OD/UNOShield_OD.ino`
- Mude o valor da variável `relayPin` para o pino que você deseja utilizar para controlar o relé
- Mude o valor de `minOxygen` para o valor que você deseja que o aerador seja ligado
- Mude o valor de `maxOxygen` para o  valor que você deseja que o aerador seja desligado
