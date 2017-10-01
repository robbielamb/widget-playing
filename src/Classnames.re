/* This is an awful way to do classnames. Don't use it.  */

type t =
  | Classname string
  | Option (string, bool);

type classnameList =
  | List t;

let classFilter (cl: t) =>
  switch cl {
  | Classname _name => true
  | Option (_name, inc) => inc
  };

let classnameExtract (cl: t) =>
  switch cl {
  | Classname name => name
  | Option (name, _) => name
  };

let classNames classnameList =>
  classnameList |> List.filter classFilter |> List.map classnameExtract |> String.concat " ";