# __[LEI] - Computação Gráfica - Fase 4__

## Grupo __30__:

- Maria Cunha - A93264
- Joana Alves - A93290
- Vicente Moireia - A93296

## __Instruções de Build:__

- __Opção 1:__ Utilizar a ferramenta _CMake_ para gerar o executável quer da aplicação _generator_, quer do _engine_. Depois de configurado e gerado, só necessita do comando _make_ na build gerada.
- __Opção 2:__ (Caso se encontre em sistemas __Unix__) Executar os seguintes passos na diretoria de cada aplicação:
  ```bash
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  ```

## __Utilização__

### __Generator__

Para a utilização genérica do generator, execute o comando:

```
./generator [SHAPE] [PARAMETERS] [FILE]
```

Para a geração de modelos baseados em curvas de Bezier é necessário executar o seguinte comando:

```
./generator patch [TESELLATION] [PATCHFILE] [FILE]
```

Em caso de erros, o generator irá providenciar instruções mais detalhadas (Para obter as intruções pode-se invocar apenas "./generator")


#
### __Engine__


Para a utilização do engine só é necessário fornecer um XML de configuração e executa-lo com:

```
./engine [XML_FILE]
```

**Nota:** A aplicação não será executada se não for fornecido este ficheiro.


#
### __Demo__

Depois do executável 'engine' gerado, mova este para a pasta demo e execute:

```
./engine solarDemo.xml
```
