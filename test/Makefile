NAME = minirt_tests

ALGELIN_DIR = ./algelin/
PARSER_DIR	= ./parser/

PARSER = test_parser
ALGELIN = test_algelin

PARSER_TEST = $(PARSER_DIR)$(PARSER)
ALGELIN_TEST = $(ALGELIN_DIR)$(ALGELIN)

all: $(NAME)

$(NAME): $(PARSER_TEST) $(ALGELIN_TEST)
	cd $(PARSER_DIR)
	$(PARSER_TEST)
	cd ..
	$(ALGELIN_TEST)

$(PARSER_TEST):
	$(MAKE) -C $(PARSER_DIR) all

$(ALGELIN_TEST):
	$(MAKE) -C $(ALGELIN_DIR) all

clean:
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(ALGELIN_DIR) clean