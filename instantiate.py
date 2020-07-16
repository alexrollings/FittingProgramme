import itertools

neutral = ["pi0", "gamma"]
bachelor = ["pi", "k"]
daughters = ["kpi", "kk", "pipi", "pik"]
charge = ["plus", "minus", "total"]

pdf_string = "Pdf<Neutral::{}, Bachelor::{}, Daughters::{}, Charge::{}>::Get(-1);"

pdf_combinations = itertools.product(neutral, bachelor, daughters, charge)

pdf_code = "void InstantiatePdfs() {\n  " + "\n  ".join(pdf_string.format(*x, *x) for x in pdf_combinations) + "\n}"

print(pdf_code)

neutral_bachelor_daughters_string = "NeutralBachelorDaughtersVars<Neutral::{}, Bachelor::{}, Daughters::{}>::Get(-1);"

neutral_bachelor_daughters_combinations = itertools.product(neutral, bachelor, daughters)

neutral_bachelor_daughters_code = "void InstantiateNeutralBachelorDaughtersVars() {\n  " + "\n  ".join(neutral_bachelor_daughters_string.format(*x, *x) for x in neutral_bachelor_daughters_combinations) + "\n}"

print(neutral_bachelor_daughters_code)

bachelor_daughters_string = "BachelorDaughtersVars<Bachelor::{}, Daughters::{}>::Get(-1);"

bachelor_daughters_combinations = itertools.product(bachelor, daughters)

bachelor_daughters_code = "void InstantiateBachelorDaughtersVars() {\n  " + "\n  ".join(bachelor_daughters_string.format(*x, *x) for x in bachelor_daughters_combinations) + "\n}"

print(bachelor_daughters_code)

neutral_bachelor_charge_string = "NeutralBachelorChargeVars<Neutral::{}, Bachelor::{}, Charge::{}>::Get(-1);"

neutral_bachelor_charge_combinations = itertools.product(neutral, bachelor, charge)

neutral_bachelor_charge_code = "void InstantiateNeutralBachelorChargeVars() {\n  " + "\n  ".join(neutral_bachelor_charge_string.format(*x, *x) for x in neutral_bachelor_charge_combinations) + "\n}"

print(neutral_bachelor_charge_code)

yields_string = "Yields<Neutral::{}, Bachelor::{}, Daughters::{}, Charge::{}>::Get(-1);"

yields_combinations = itertools.product(neutral, bachelor, daughters, charge)

yields_code = "void InstantiateYields() {\n  " + "\n  ".join(yields_string.format(*x, *x) for x in yields_combinations) + "\n}"

print(yields_code)

neutral_bachelor_string = "NeutralBachelorVars<Neutral::{}, Bachelor::{}>::Get(-1);"

neutral_bachelor_combinations = itertools.product(neutral, bachelor)

neutral_bachelor_code = "void InstantiateNeutralBachelorVars() {\n  " + "\n  ".join(neutral_bachelor_string.format(*x, *x) for x in neutral_bachelor_combinations) + "\n}"

print(neutral_bachelor_code)

neutral_daughters_string = "NeutralDaughtersVars<Neutral::{}, Daughters::{}>::Get(-1);"

neutral_daughters_combinations = itertools.product(neutral, daughters)

neutral_daughters_code = "void InstantiateNeutralDaughtersVars() {\n  " + "\n  ".join(neutral_daughters_string.format(*x, *x) for x in neutral_daughters_combinations) + "\n}"

print(neutral_daughters_code)

neutral_string = "NeutralVars<Neutral::{}>::Get(-1);"

neutral_combinations = neutral

neutral_code = "void InstantiateNeutralVars() {\n  " + "\n  ".join(neutral_string.format(x, x) for x in neutral_combinations) + "\n}"

print(neutral_code)
