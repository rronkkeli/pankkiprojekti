
DELIMITER //
DROP procedure IF EXISTS nostotapahtuma;
CREATE PROCEDURE nostotapahtuma(IN asiakas INT,IN tilin_numero INT, IN nosto DECIMAL(10,2))
BEGIN
    DECLARE tarkistettava_balance DECIMAL(10,2);

    SELECT balance INTO tarkistettava_balance 
    FROM account 
    WHERE idaccount = tilin_numero;

 IF EXISTS (SELECT * FROM customer_has_account WHERE idcustomer = asiakas AND idaccount = tilin_numero) THEN
        IF tarkistettava_balance IS NOT NULL AND tarkistettava_balance >0 AND tarkistettava_balance-nosto>=0 THEN
        UPDATE account 
        SET balance = balance - nosto 
        WHERE idaccount = tilin_numero;
        INSERT INTO withdrawal(idaccount, amount, timestamp) VALUES (tilin_numero, nosto, NOW());

        ELSEIF  tarkistettava_balance-nosto < 0 THEN
            SELECT 'You do not have enought money for that sum';

        ELSE
            SELECT 'You have no balance, U broke :)';

        END IF;
ELSE
    SELECT 'You do not have accest to that account';
END IF;

END//

DROP procedure IF EXISTS tilitiedot;

CREATE PROCEDURE tilitiedot(IN asiakas INT)
BEGIN

       SELECT idwithdrawal, withdrawal.idaccount, amount, timestamp
    FROM withdrawal

    JOIN account ON withdrawal.idaccount = account.idaccount
    JOIN customer_has_account ON account.idaccount = customer_has_account.idaccount
    WHERE asiakas = customer_has_account.idcustomer ORDER BY idwithdrawal desc;
END//

DROP PROCEDURE IF EXISTS tilit_ja_kortit;
    
CREATE PROCEDURE tilit_ja_kortit(IN asiakas INT)
BEGIN

    SELECT account.idaccount, account.balance, credit
    FROM customer
    JOIN customer_has_account ON customer.idcustomer = customer_has_account.idcustomer
    JOIN account ON customer_has_account.idaccount = account.idaccount
    WHERE asiakas = customer.idcustomer;

    SELECT idaccount, card.idcard, pin
    FROM card
    JOIN card_has_account ON card.idcard = card_has_account.idcard
    WHERE asiakas = idcustomer;

END//

DROP procedure IF EXISTS new_card;
CREATE PROCEDURE new_card(IN use_customer INT,IN combine_account INT, IN combine_account2 INT, IN newcardcode VARCHAR(255),IN new_pin VARCHAR(225))

BEGIN

    DECLARE account_type1 VARCHAR(50);
    DECLARE account_type2 VARCHAR(50);
    SELECT credit INTO account_type1 FROM account WHERE idaccount = combine_account;
    SELECT credit INTO account_type2 FROM account WHERE idaccount = combine_account2;

IF combine_account2 IS NULL THEN
  IF EXISTS(SELECT 1 FROM account WHERE idaccount = combine_account) THEN
      IF NOT EXISTS(SELECT 1 FROM card WHERE idcard = newcardcode) THEN
          INSERT INTO card(idcard, pin, idcustomer) VALUES(newcardcode,new_pin, use_customer);
          INSERT INTO card_has_account(idcard,idaccount) VALUES (newcardcode, combine_account);
          SELECT 'SUCCHEESE';
       ELSE
          SELECT 'Card already exists';
          END IF;
  ELSE
      SELECT 'Account does not exist';
  END IF;
ELSE 
  IF EXISTS(SELECT 1 FROM account WHERE idaccount = combine_account) THEN
      IF EXISTS(SELECT 1 FROM account WHERE idaccount = combine_account2) THEN
          IF account_type1 IS NULL XOR account_type2 IS NULL THEN
                 IF NOT EXISTS(SELECT 1 FROM card WHERE idcard = newcardcode) THEN
                     INSERT INTO card(idcard, pin, idcustomer) VALUES(newcardcode,new_pin, use_customer);
                      INSERT INTO card_has_account(idcard,idaccount) VALUES (newcardcode, combine_account);
                      INSERT INTO card_has_account(idcard,idaccount) VALUES (newcardcode, combine_account2);
                      SELECT 'SUCCEES';
               ELSE
                   SELECT 'Card already exists';
               END IF;
           ELSE
               SELECT 'Accounts are the same type';
           END IF;
       ELSE
           SELECT 'Credit accout does not exists';
       END IF;
   ELSE
       SELECT 'Debit account does not exists ' ;
   END IF;
END IF;
END//
    
DELIMITER ;
