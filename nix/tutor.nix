{ docBase }: 

{
  intro = builtins.trace ''
    ========================================================
     🎮 NIX COMPREHENSIVE MASTER TUTOR 🎮
    ========================================================
    Welcome back to the native REPL. Auto-complete is ACTIVE.
    
    Modules Available:
      m1 - Basics & Builtins
      m2 - Strings & Interpolation
      
    To begin, type: `m1.q1.question`
    To submit, type: `m1.q1.check (your_code)`
    ========================================================
  '' "Ready.";

  m1 = {
    q1 = {
      question = "Extract a list of keys from `{ x = 10; y = 20; }`.";
      check = input:
        if input == [ "x" "y" ] then
          "✅ Correct! Proceed to `m1.q2.question`"
        else
          "❌ Incorrect. Review: ${docBase}/language/builtins.html";
    };
    
    q2 = {
      question = "Filter `[ 1 2 3 4 5 ]` to keep numbers greater than 3.";
      check = input:
        if input == [ 4 5 ] then
          "✅ Correct! Proceed to module 2: `m2.q1.question`"
        else
          "❌ Incorrect. Review: ${docBase}/language/builtins.html";
    };
  };

  m2 = {
    q1 = {
      question = "Evaluate an interpolated string that joins 'Hello' and 'Nix' with a space.";
      check = input:
        if input == "Hello Nix" then
          "✅ Correct! You are a master."
        else
          "❌ Incorrect. Review: ${docBase}/language/values.html";
    };
  };
}
